#include "Field.hpp"
#include "PowerUp/PassUp.hpp"
#include "PowerUp/SpeedUp.hpp"
#include "PowerUp/FireUp.hpp"
#include "PowerUp/BombUp.hpp"
#include "Bomb.hpp"
#include "Sparks.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Bomberman {

Field::Field(const std::vector<PlayerMeta> &players, Env env) :
	m_env(env),
	m_tiles(genTiles()),
	m_w(m_tiles.at(0).size()),
	m_h(m_tiles.size()),
	m_camera(add<Camera>(m_w, m_h)),
	m_wall(add<Tile>(Tile::Type::Wall, irr::core::vector2di(-1000, -1000), *this)),
	m_players_alive(0)
{
	addBarrier();
	size_t id = 0;
	size_t player_id = 0;
	for (auto &m : players) {
		auto &p = addMob<Player>(m.is_bot, m.name.size() == 0 ? id_to_str(id) : m.name, id, player_id);
		bindPlayer(p);
		m_players_alive++;
		if (!m.is_bot)
			player_id++;
		id++;
	}
	init();
}

void Field::init(void)
{
	bind(world.session.events.key.pressed, [&](auto key){
		if (key == irr::KEY_ESCAPE)
			session.switch_Pause = true;
		else if (key == irr::KEY_RETURN) {
			std::ofstream save("save.BOMBS", std::ios::trunc | std::ios::binary);

			write(save);
		} else if (key == irr::KEY_RSHIFT) {
			session.load_game = true;
		}
	});
}

void Field::bindPlayer(Player &p)
{
	m_players.emplace_back(p);
	bind(p.died, [&](){
		m_players_alive--;
		if (m_players_alive == 1) {
			for (auto &p : m_players)
				if (!p.get().isDead()) {
					std::cout << "PLAYER " << p.get().getName() << " WON!!" << std::endl;
					game_done.emit();
				}
		}
	});
}

void Field::write(std::ostream &o)
{
	en::util::write(o, m_env);
	en::util::write(o, m_w);
	en::util::write(o, m_h);
	for (auto &r : m_tiles)
		for (auto &t : r)
			t.get().write(o);
	m_wall.write(o);
}

std::vector<std::vector<std::reference_wrapper<Tile>>> Field::readTiles(std::istream &i)
{
	std::vector<std::vector<std::reference_wrapper<Tile>>> res;
	auto w = en::util::read<size_t>(i);
	auto h = en::util::read<size_t>(i);

	for (size_t it = 0; it < h; it++) {
		std::vector<std::reference_wrapper<Tile>> row;
		for (size_t j = 0; j < w; j++)
			row.emplace_back(add<Tile>(i, *this));
		res.emplace_back(std::move(row));
	}
	return res;
}

Field::Field(std::istream &i) :
	m_env(en::util::read<decltype(m_env)>(i)),
	m_tiles(readTiles(i)),
	m_w(m_tiles.at(0).size()),
	m_h(m_tiles.size()),
	m_camera(add<Camera>(m_w, m_h)),
	m_wall(add<Tile>(i, *this)),
	m_players_alive(0)
{
	addBarrier();
	for (auto &r : m_tiles)
		for (auto &t : r)
			for (auto &m : t.get().getMobs()) {
				auto &mob = m.get();
				try {
					auto &player = dynamic_cast<Player&>(mob);
					bindPlayer(player);
				} catch (const std::bad_cast&) {}
			}
	init();
}

Field::~Field(void)
{
	for (auto &e : getChildren()) {
		try {
			auto &mob = dynamic_cast<Mob&>(e);
			mob.destroy();
		} catch (const std::bad_cast&) {}
	}
	collectGarbage();
}

Tile& Field::at(const irr::core::vector2di &pos)
{
	if (pos.Y >= 0 && pos.Y < (int)m_tiles.size()) {
		auto &row = m_tiles.at(pos.Y);
		if (pos.X >= 0 && pos.X < (int)row.size())
			return row.at(pos.X);
	}
	return m_wall;
}

Tile::Type Field::typeAt(const irr::core::vector2di &pos)
{
	return at(pos).getType();
}

void Field::nuke(const irr::core::vector2di &pos, bool is_simulation)
{
	if (is_simulation) {
		m_bombs.at(pos.Y).at(pos.X) = true;
	} else {
		if (typeAt(pos) == Tile::Type::Box)
			genItem(pos);
		at(pos).setType(Tile::Type::Air);
	}
}

void Field::genItem(const irr::core::vector2di &pos)
{
	static const std::vector<std::pair<size_t, const std::function<void (void)>>> items = {
		{1, [&](){
			addMob<PowerUp::PassUp>(pos);
		}},
		{2, [&](){
			addMob<PowerUp::SpeedUp>(pos);
		}},
		{2, [&](){
			addMob<PowerUp::FireUp>(pos);
		}},
		{3, [&](){
			addMob<PowerUp::BombUp>(pos);
		}},
		{8, [](){
		}}
	};
	size_t sum = 0;

	for (auto &p : items)
		sum += p.first;

	size_t got = world.session.randInt(sum);

	size_t goti = 0;
	for (auto &p : items) {
		if (goti >= got) {
			p.second();
			return;
		}
		goti += p.first;
	}
}

size_t Field::getWidth(void) const
{
	return m_w;
}

size_t Field::getHeight(void) const
{
	return m_h;
}

void Field::updateBombMap(void)
{
	m_bombs.clear();

	for (size_t i = 0; i < m_h; i++) {
		std::vector<bool> row;
		for (size_t j = 0; j < m_w; j++)
			row.emplace_back(false);
		m_bombs.emplace_back(std::move(row));
	}
	for (auto &r : m_tiles)
		for (auto &t : r)
			for (auto &m : t.get().getMobs()) {
				auto &mob = m.get();
				try {
					dynamic_cast<Bomb&>(mob).nuke(true);
				} catch (const std::bad_cast&) {}
				try {
					dynamic_cast<Sparks&>(mob).simulate();
				} catch (const std::bad_cast&) {}
			}
}

bool Field::isBombed(const irr::core::vector2di &pos)
{
	if (pos.Y >= 0 && pos.Y < (int64_t)m_h && pos.X >= 0 && pos.X < (int64_t)m_w)
		return m_bombs.at(pos.Y).at(pos.X);
	else
		return false;
}

bool Field::anySpark(const irr::core::vector2di &pos)
{
	for (auto &m : at(pos).getMobs()) {
		try {
			auto &s = dynamic_cast<Sparks&>(m.get());
			if (s.stillDeadly())
				return true;
		} catch (const std::bad_cast&) {}
	}
	return false;
}

std::vector<std::reference_wrapper<Player>> Field::getPlayers(void)
{
	return m_players;
}

std::string Field::id_to_str(size_t id)
{
	std::stringstream ss;

	ss << (id + 1);
	return ss.str();
}

std::vector<std::vector<Tile::Type>> Field::genField(void)
{
	std::vector<std::vector<Tile::Type>> res;
	size_t h = 10;
	size_t w = 14;
	int wi = w;
	int hi = h;
	std::vector<irr::core::vector2di> air = {
		{0, 0},
		{1, 0},
		{0, 1},

		{wi - 1, hi - 1},
		{wi - 2, hi - 1},
		{wi - 1, hi - 2},

		{wi - 1, 0},
		{wi - 2, 0},
		{wi - 1, 1},

		{0, hi - 1},
		{1, hi - 1},
		{0, hi - 2},
	};

	for (size_t i = 0; i < h; i++) {
		std::vector<Tile::Type> row;
		for (size_t j = 0; j < w; j++) {
			auto p = irr::core::vector2di(j, i);
			auto type = Tile::Type::Air;
			bool isAir = false;
			size_t random_number = world.session.randInt(6);
			for (auto &a : air)
				if (a == p)
					isAir = true;
			if (!isAir) {
				if (random_number == 0)
					type = Tile::Type::Wall;
				else if (random_number == 1)
					type = Tile::Type::Air;
				else
					type = Tile::Type::Box;
			}
			row.emplace_back(type);
		}
		res.emplace_back(row);
	}
	return res;
}

const std::string& Field::typeToTexture(Tile::Type type)
{
	static const std::map<Env, std::map<Tile::Type, std::string>> table = {
		{Env::Overworld, {
			{Tile::Type::Box, "res/models/crate.jpg"},
			{Tile::Type::Wall, "res/models/wall.jpg"},
			{Tile::Type::Air, "res/models/crate.jpg"},
			{Tile::Type::Ground, "res/models/grass.jpg"}
		}}, {Env::Mario, {
			{Tile::Type::Box, "res/models/mario-box.jpg"},
			{Tile::Type::Wall, "res/models/mario-wall.jpg"},
			{Tile::Type::Air, "res/models/crate.jpg"},
			{Tile::Type::Ground, "res/models/grass.jpg"}
		}}
	};

	return table.at(m_env).at(type);
}

std::vector<std::vector<std::reference_wrapper<Tile>>> Field::genTiles(void)
{
	std::vector<std::vector<std::reference_wrapper<Tile>>> res;

	auto field = genField();
	for (size_t i = 0; i < field.size(); i++) {
		auto &field_row = field.at(i);
		std::vector<std::reference_wrapper<Tile>> row;
		for (size_t j = 0; j < field_row.size(); j++)
			row.emplace_back(add<Tile>(field_row.at(j), irr::core::vector2di(j, i), *this));
		res.emplace_back(row);
	}
	return res;
}

void Field::addBarrier(void)
{
	int64_t radius = 1;
	for (int64_t i = -radius; i < ((int64_t)m_h + radius); i++)
		for (int64_t j = -radius; j < ((int64_t)m_w + radius); j++) {
			if (!((i >= 0 && i < (int64_t)m_h) && (j >= 0 && j < (int64_t)m_w)))
				add<Tile>(Tile::Type::Wall, irr::core::vector2di(j, i), *this);
		}
	
	radius = 7;
	for (int64_t i = -radius; i < ((int64_t)m_h + radius); i++)
		for (int64_t j = -radius; j < ((int64_t)m_w + radius); j++) {
			add<Tile>(Tile::Type::Ground, irr::core::vector2di(j, i), *this, -1);
		}
}

}