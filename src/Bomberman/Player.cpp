#include <optional>
#include "Player.hpp"
#include "Bomb.hpp"
#include "PowerUp/Base.hpp"

namespace Bomberman {

Player::Player(bool is_bot, const std::string &name, size_t id, size_t player_id) :
	Mob("res/models/bomberman.obj", "res/models/mario-box.jpg"),
	m_bombs(1),
	m_time_before_bomb(reload_rate),
	m_dead(false),
	m_name(name),
	m_is_bot(is_bot),
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
			botUpdate();
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
	botUpdate();
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

void Player::botUpdate(void)
{
	static const std::vector<irr::core::vector2di> dirs = {
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1},
	};

	if (!m_is_bot)
		return;

	field.updateBombMap();
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
	if (depth > 128)
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

double Player::reload_rate = 3.0;

std::unique_ptr<Player::Controller> Player::genController(bool is_bot, size_t player_id)
{
	static const std::map<size_t, LocalController::Layout> layouts = {
		{0, LocalController::Layout::Zqsd},
		{1, LocalController::Layout::Arrows},
		{2, LocalController::Layout::Oklm},
		{3, LocalController::Layout::Yghj},
	};

	if (is_bot)
		return std::make_unique<BotController>(field, *this);
	else
		return std::make_unique<LocalController>(world.session, layouts.at(player_id));
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

Player::LocalController::LocalController(en::Session &session, Layout layout) :
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

const std::map<Player::Controller::Key, irr::EKEY_CODE>& Player::LocalController::getKeySet(Layout layout)
{
	static const std::map<Layout, std::map<Key, irr::EKEY_CODE>> layouts = {
		{Layout::Zqsd, {
			{Key::Left, irr::KEY_KEY_Q},
			{Key::Right, irr::KEY_KEY_D},
			{Key::Up, irr::KEY_KEY_Z},
			{Key::Down, irr::KEY_KEY_S},
			{Key::Fire, irr::KEY_KEY_E}
		}},
		{Layout::Arrows, {
			{Key::Left, irr::KEY_LEFT},
			{Key::Right, irr::KEY_RIGHT},
			{Key::Up, irr::KEY_UP},
			{Key::Down, irr::KEY_DOWN},
			{Key::Fire, irr::KEY_RCONTROL}
		}},
		{Layout::Oklm, {
			{Key::Left, irr::KEY_KEY_K},
			{Key::Right, irr::KEY_KEY_M},
			{Key::Up, irr::KEY_KEY_O},
			{Key::Down, irr::KEY_KEY_L},
			{Key::Fire, irr::KEY_KEY_P}
		}},
		{Layout::Yghj, {
			{Key::Left, irr::KEY_KEY_G},
			{Key::Right, irr::KEY_KEY_J},
			{Key::Up, irr::KEY_KEY_Y},
			{Key::Down, irr::KEY_KEY_H},
			{Key::Fire, irr::KEY_KEY_U}
		}}
	};

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