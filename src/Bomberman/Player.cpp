#include <optional>
#include <fstream>
#include <sstream>
#include "Player.hpp"
#include "Bomb.hpp"
#include "PowerUp/Base.hpp"

namespace Bomberman {

Player::Player(bool is_bot, const std::string &name, size_t id, size_t player_id) :
	Mob("res/models/bomberman.obj", "res/env/mario/box.jpg"),
	m_bombs(1),
	m_time_before_bomb(reload_rate),
	m_dead(false),
	m_name(name),
	m_is_bot(is_bot),
	m_difficulty(world.session.m_options.level),
	m_bot_it(levelToBotIt(m_difficulty)),
	m_bot_next_action(0.0),
	m_player_id(player_id),
	m_controller(genController(is_bot, player_id))
{
	int w_max = field.getWidth() - 1;
	int h_max = field.getHeight() - 1;
	const std::map<size_t, irr::core::vector2di> spawns = {
		{2, {0, 0}},
		{3, {w_max, 0}},
		{0, {0, h_max}},
		{1, {w_max, h_max}},
	};

	setPos(irr::core::vector2di(spawns.at(id)));

	init();
}

void Player::init(void)
{
	setScale(irr::core::vector3df(1.0));

	static const std::map<Controller::Key, irr::core::vector2di> directions = {
		{Controller::Key::Up, irr::core::vector2di(0, 1)},
		{Controller::Key::Down, irr::core::vector2di(0, -1)},
		{Controller::Key::Left, irr::core::vector2di(-1, 0)},
		{Controller::Key::Right, irr::core::vector2di(1, 0)}
	};

	if (m_dead)
		setScale(irr::core::vector3df(0.0));
	bind(world.events.update, [&](auto deltaTime) {
		m_controller->scan();

		if (!m_dead) {
			for (auto &p : directions)
				if (m_controller->getState(p.first))
					if (move(p.second, m_stats.speed))
						world.session.playSoundRnd("res/sounds/footstep", 4);

			m_time_before_bomb -= deltaTime;
			if (m_time_before_bomb <= 0.0) {
				m_bombs++;
				if (m_bombs > m_stats.max_bombs)
					m_bombs = m_stats.max_bombs;
				m_time_before_bomb += reload_rate;
			}

			if (m_controller->isPressed(Controller::Key::Fire)) {
				if (m_bombs > 0) {
					world.session.playSound("res/sounds/putbomb.ogg", 0.75);
					world.session.playSound("res/sounds/bombfuse.ogg", 0.1);
					field.addMob<Bomb>(getIncomingPos(), m_stats.bomb_radius);
					m_bombs--;
				}
			}
		}

		if (!isMoving())
			botUpdate(deltaTime);
	});
}

void Player::write(std::ostream &o)
{
	en::util::write(o, en::util::type_id<decltype(*this)>());

	Mob::write(o);
	en::util::write(o, m_stats);
	en::util::write(o, m_bombs);
	en::util::write(o, m_time_before_bomb);
	en::util::write(o, m_dead);
	en::util::write_string(o, m_name),
	en::util::write(o, m_is_bot);
	en::util::write(o, m_difficulty);
	en::util::write(o, m_bot_it);
	en::util::write(o, m_bot_next_action);
	en::util::write(o, m_player_id);
}

Player::Player(std::istream &i) :
	Mob(i),
	m_stats(en::util::read<decltype(m_stats)>(i)),
	m_bombs(en::util::read<decltype(m_bombs)>(i)),
	m_time_before_bomb(en::util::read<decltype(m_time_before_bomb)>(i)),
	m_dead(en::util::read<decltype(m_dead)>(i)),
	m_name(en::util::read_string(i)),
	m_is_bot(en::util::read<decltype(m_is_bot)>(i)),
	m_difficulty(en::util::read<decltype(m_difficulty)>(i)),
	m_bot_it(en::util::read<decltype(m_bot_it)>(i)),
	m_bot_next_action(en::util::read<decltype(m_bot_next_action)>(i)),
	m_player_id(en::util::read<decltype(m_player_id)>(i)),
	m_controller(genController(m_is_bot, m_player_id))
{
	init();
}

Player::~Player(void)
{
}

void Player::hitByBomb(void)
{
	if (m_dead)
		return;
	m_dead = true;
	setScale(irr::core::vector3df(0.0));
	world.session.playSoundRnd("res/sounds/death", 3);
	died.emit();
}

bool Player::isDead(void) const
{
	return m_dead;
}

const std::string& Player::getName(void) const
{
	return m_name;
}

bool Player::canMoveTo(const irr::core::vector2di &pos) const
{
	auto t = field.typeAt(pos);

	if (m_stats.wall_pass)
		return t == Tile::Type::Air || t == Tile::Type::Box;
	else
		return t == Tile::Type::Air;
}

void Player::onMove(const irr::core::vector2di &newpos)
{
	for (auto &m : field.at(newpos).getMobs()) {
		auto &mob = m.get();
		try {
			dynamic_cast<PowerUp::Base&>(mob).collect(*this);
		} catch (const std::bad_cast&) {}
	}
	if (m_stats.wall_pass) {
		if (m_stats.wall_pass_used) {
			if (field.typeAt(getPos()) == Tile::Type::Air) {
				m_stats.wall_pass = false;
				m_stats.wall_pass_used = false;
			}
		} else {
			if (field.typeAt(getPos()) == Tile::Type::Box)
				m_stats.wall_pass_used = true;
		}
	}
	botUpdate(0.0);
}

void Player::onAnim(double ratio)
{
	auto s = sin(ratio * (M_PI * 2.0));
	setRot(irr::core::vector3df(13.0 * s, getAngleStart() * (1.0 - ratio) + getAngleEnd() * ratio, s * 5.0));
}

bool Player::isSafeToGo(const irr::core::vector2di &pos)
{
	return !field.isBombed(pos) && canMoveTo(pos);
}

Player::Controller::Key Player::dirToKey(const irr::core::vector2di &dir)
{
	static const std::map<irr::core::vector2di, Player::Controller::Key> keys = {
		{{-1, 0}, Controller::Key::Left},
		{{1, 0}, Controller::Key::Right},
		{{0, 1}, Controller::Key::Up},
		{{0, -1}, Controller::Key::Down},
	};

	return keys.at(dir);
}

irr::core::vector2df Player::ivectof(const irr::core::vector2di &vec)
{
	return irr::core::vector2df(vec.X, vec.Y);
}

irr::core::vector2di Player::nearestPlayerVec(void)
{
	std::optional<irr::core::vector2di> res;

	for (auto &p : field.getPlayers()) {
		auto &pl = p.get();
		if (&pl == this || pl.isDead())
			continue;
		auto v = pl.getPos() - getPos();
		if (!res || (ivectof(v).getLength() < ivectof(*res).getLength()))
			res = v;
	}
	if (res)
		return *res;
	else
		return irr::core::vector2di(0, 0);
}

void Player::botUpdate(double delta)
{
	static const std::vector<irr::core::vector2di> dirs = {
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1},
	};

	static const std::map<size_t, double> idle_table = {
		{0, 2.0},
		{1, 1.5},
		{2, 1.0},
		{3, 0.5},
		{4, 0.0},
	};

	if (!m_is_bot)
		return;

	field.updateBombMap();
	auto mul = 1.0;
	if (field.isBombed(getPos()))
		mul *= 4.0;
	m_bot_next_action -= delta * mul;
	if (m_bot_next_action <= 0) {
		m_bot_next_action += world.session.rand() * idle_table.at(m_difficulty);
		if (m_bot_next_action < 0.0)
			m_bot_next_action = 0.0;
		if (field.isBombed(getPos())) {
			if (!botEscape(getPos())) {}
				//std::cout << m_name << ": well im fucked :(" << std::endl;
		} else {
			shouldPutBomb();
			{
				field.updateBombMap();
				auto n = nearestPlayerVec();
				auto nf = irr::core::vector2df(n.X, n.Y);
				std::map<double, irr::core::vector2di> table;

				for (auto &d : dirs)
					if (isSafeToGo(getPos() + d)) {
						double prod = ivectof(d).dotProduct(nf);
						if (prod >= 0.0)
							table.emplace(prod, d);
					}
				if (table.size() > 0)
					m_next_bot_moves.emplace(dirToKey(table.rbegin()->second));
			}
		}
	}
}

void Player::insertEntry(std::map<size_t, irr::core::vector2di> &res, const irr::core::vector2di &dir, size_t depth)
{
	if (res.find(depth) != res.end())
		return;
	else
		res.emplace(depth, dir);
}

void Player::fillRange(size_t range[4])
{
	size_t i = 0;
	bool done[4] = {false, false, false, false};

	while (true) {
		size_t got = world.session.randInt(4);
		if (!done[got]) {
			range[i++] = got;
			done[got] = true;
		}
		if (i == 4)
			return;
	}
}

void Player::checkDir(const irr::core::vector2di &basedir, const irr::core::vector2di &pos, const irr::core::vector2di &dir, size_t depth, std::map<size_t, irr::core::vector2di> &res, std::vector<irr::core::vector2di> &path)
{
	static const std::vector<irr::core::vector2di> dirs = {
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1},
	};
	size_t range[4];
	fillRange(range);

	auto p = pos + dir;

	for (size_t i = 0; i < path.size(); i++)
		if (path.rbegin()[i] == p)
			return;

	if (res.size() > 0) {
		if (res.begin()->first <= depth)
			return;
	}
	if (depth > m_bot_it)
		return;

	if (!(p.X >= 0 && p.X < (int64_t)field.getWidth() && p.Y >= 0 && p.Y < (int64_t)field.getHeight()))
		return;

	if (field.anySpark(p))
		return;

	if (isSafeToGo(p))
		insertEntry(res, basedir, depth);
	if (canMoveTo(p)) {
		path.emplace_back(p);
		for (size_t i = 0; i < 4; i++)
			checkDir(basedir, p, dirs.at(range[i]), depth + 1, res, path);
		path.pop_back();
	}
}

bool Player::botEscape(const irr::core::vector2di &pos)
{
	static const std::vector<irr::core::vector2di> dirs = {
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1},
	};
	static const auto zero = irr::core::vector2di(0, 0);
	size_t range[4];
	fillRange(range);

	std::map<size_t, irr::core::vector2di> res;
	std::vector<irr::core::vector2di> path;

	for (size_t i = 0; i < 4; i++)
		checkDir(dirs.at(range[i]), pos, dirs.at(range[i]), 0, res, path);
	if (res.size() == 0)
		return false;
	else {
		if (res.begin()->second != zero)
			m_next_bot_moves.emplace(dirToKey(res.begin()->second));
		return true;
	}
}

bool Player::shouldPutBomb(void)
{
	if (m_bombs == 0)
		return false;

	static const std::vector<irr::core::vector2di> dirs = {
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1},
	};

	bool found_box = false;
	for (auto &d : dirs)
		if (field.typeAt(getPos() + d) == Tile::Type::Box)
			found_box = true;

	if (!found_box)
		if (ivectof(nearestPlayerVec()).getLength() > 6.0)
			return false;

	auto &b = field.addMob<Bomb>(getPos(), m_stats.bomb_radius);

	field.updateBombMap();
	auto res = botEscape(getPos());
	while (m_next_bot_moves.size() > 0)
		m_next_bot_moves.pop();
	if (!res)
		b.defuze();
	else {
		world.session.playSound("res/sounds/putbomb.ogg", 0.75);
		world.session.playSound("res/sounds/bombfuse.ogg", 0.1);
		m_bombs--;
	}
	return res;
}

Player::Stats& Player::getStats(void)
{
	return m_stats;
}

size_t Player::levelToBotIt(size_t level)
{
	static const std::map<size_t, size_t> table = {
		{0, 1},
		{1, 2},
		{2, 3},
		{3, 6},
		{4, 64}
	};

	return table.at(level);
}

double Player::reload_rate = 3.0;

std::unique_ptr<Player::Controller> Player::genController(bool is_bot, size_t player_id)
{
	if (is_bot)
		return std::make_unique<BotController>(field, *this);
	else
		return std::make_unique<LocalController>(world.session, player_id + 1);
}

void Player::Controller::scan(void)
{
	refresh();
	m_last_state = m_cur_state;
	for (auto &k : getKeys())
		m_cur_state[k] = getState(k);
}

bool Player::Controller::isPressed(Key key)
{
	return !m_last_state[key] && m_cur_state[key];
}

bool Player::Controller::isReleased(Key key)
{
	return m_last_state[key] && !m_cur_state[key];
}

const std::vector<Player::Controller::Key>& Player::Controller::getKeys(void)
{
	static const std::vector<Player::Controller::Key> res = {
		Key::Up,
		Key::Down,
		Key::Left,
		Key::Right,
		Key::Fire
	};

	return res;
}

Player::LocalController::LocalController(en::Session &session, size_t layout) :
	m_session(session),
	m_layout(layout),
	m_key_set(getKeySet(layout))
{
}

Player::LocalController::~LocalController(void)
{
}

void Player::LocalController::refresh(void)
{
}

bool Player::LocalController::getState(Key key) const
{
	return m_session.events.key.getState(getKeyCode(key));
}

std::map<size_t, std::map<Player::Controller::Key, irr::EKEY_CODE>> Player::LocalController::loadBindings(void)
{
	static const std::map<std::string, irr::EKEY_CODE> key_table {
		{"a", irr::KEY_KEY_A},
		{"b", irr::KEY_KEY_B},
		{"c", irr::KEY_KEY_C},
		{"d", irr::KEY_KEY_D},
		{"e", irr::KEY_KEY_E},
		{"f", irr::KEY_KEY_F},
		{"g", irr::KEY_KEY_G},
		{"h", irr::KEY_KEY_H},
		{"i", irr::KEY_KEY_I},
		{"j", irr::KEY_KEY_J},
		{"k", irr::KEY_KEY_K},
		{"l", irr::KEY_KEY_L},
		{"m", irr::KEY_KEY_M},
		{"n", irr::KEY_KEY_N},
		{"o", irr::KEY_KEY_O},
		{"p", irr::KEY_KEY_P},
		{"q", irr::KEY_KEY_Q},
		{"r", irr::KEY_KEY_R},
		{"s", irr::KEY_KEY_S},
		{"t", irr::KEY_KEY_T},
		{"u", irr::KEY_KEY_U},
		{"v", irr::KEY_KEY_V},
		{"w", irr::KEY_KEY_W},
		{"x", irr::KEY_KEY_X},
		{"y", irr::KEY_KEY_Y},
		{"z", irr::KEY_KEY_Z},
		{"space", irr::KEY_SPACE},
		{"lcontrol", irr::KEY_LCONTROL},
		{"rcontrol", irr::KEY_RCONTROL},
		{"lshift", irr::KEY_LSHIFT},
		{"rshift", irr::KEY_RSHIFT},
		{"enter", irr::KEY_RETURN},
		{"backspace", irr::KEY_BACK},
		{"left", irr::KEY_LEFT},
		{"right", irr::KEY_RIGHT},
		{"up", irr::KEY_UP},
		{"down", irr::KEY_DOWN}
	};

	static const std::map<std::string, Key> id_table = {
		{"left", Key::Left},
		{"right", Key::Right},
		{"up", Key::Up},
		{"down", Key::Down},
		{"fire", Key::Fire}
	};

	std::map<size_t, std::map<Key, irr::EKEY_CODE>> res;

	std::ifstream file("controls.txt");

	size_t cur_binding;
	std::optional<std::map<Key, irr::EKEY_CODE>> cur;
	std::string line;
	while (std::getline(file, line)) {
		line = en::util::strip_string(line);
		for (auto &c : line)
			if (c >= 'A' && c <= 'Z')
				c += 32;

		if (line.size() == 0)
			continue;
		if (cur) {
			std::stringstream ss(line);
			std::string id, val;
			std::getline(ss, id, '=');
			std::getline(ss, val, '=');

			auto k = id_table.find(id);
			if (k == id_table.end())
				throw std::runtime_error(std::string("Can't find game key id: '") + id + std::string("'"));
			auto v = key_table.find(val);
			if (v == key_table.end())
				throw std::runtime_error(std::string("Can't find irrlicht key id: '") + val + std::string("'"));
			if (cur->find(k->second) != cur->end())
				throw std::runtime_error(std::string("Rebinding key id: '") + id + std::string("'"));
			cur->emplace(k->second, v->second);

			if (cur->size() == 5) {
				res[cur_binding] = *cur;
				cur.reset();
			}
		} else {
			if (line.at(0) != 'p')
				throw std::runtime_error("Expected character P");
			line.erase(line.begin());
			cur_binding = en::util::conv_safe(std::stoull, line);
			cur = std::map<Key, irr::EKEY_CODE>();
		}
	}

	return res;
}

const std::map<Player::Controller::Key, irr::EKEY_CODE>& Player::LocalController::getKeySet(size_t layout)
{
	static const std::map<size_t, std::map<Key, irr::EKEY_CODE>> layouts = loadBindings();

	return layouts.at(layout);
}

irr::EKEY_CODE Player::LocalController::getKeyCode(Key abstract_key) const
{
	return m_key_set.at(abstract_key);
}

Player::BotController::BotController(Field &field, Player &me) :
	m_field(field),
	m_me(me)
{
}

Player::BotController::~BotController(void)
{
}

void Player::BotController::refresh(void)
{
	auto &keys = getKeys();
	std::map<Key, bool> to_press;

	while (m_me.m_next_bot_moves.size() > 0) {
		auto &cur = m_me.m_next_bot_moves.front();
		to_press[cur] = true;
		m_me.m_next_bot_moves.pop();
	}
	for (auto &k : keys)
		m_keys[k] = to_press[k];
}

bool Player::BotController::getState(Key key) const
{
	return m_keys.at(key);
}

}