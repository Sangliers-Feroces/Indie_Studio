#include "Field.hpp"

#include <iostream>

namespace Bomberman {

Field::Field(void) :
	m_tiles(genTiles()),
	m_w(m_tiles.at(0).size()),
	m_h(m_tiles.size()),
	m_camera(add<Camera>(m_w, m_h)),
	m_player(add<Player>()),
	m_wall(add<Tile>(Tile::Type::Wall, irr::core::vector2di(-1000, -1000)))
{
	for (int64_t i = -50; i < 50; i++)
		for (int64_t j = -50; j < 50; j++) {
			if (!((i >= 0 && i < m_h) && (j >= 0 && j < m_w)))
				add<Tile>(Tile::Type::Wall, irr::core::vector2di(j, i));
		}

	bind(m_player.pressedZ, [](){
		std::cout << "Player pressed Z!!" << std::endl;
	});

	bind(m_player.message, [](const std::string &msg){
		std::cout << "Player messages you!!: " << msg << std::endl;
	});

	bind(m_player.do_quit, [](){
		std::cout << "Player wants to quit!!" << std::endl;
		std::cout << "(someone please add a method in Session to break game loop)" << std::endl;
	});
}

Field::~Field(void)
{
}

Tile& Field::at(const irr::core::vector2di &pos)
{
	if (pos.Y >= 0 && pos.Y < m_tiles.size()) {
		auto &row = m_tiles.at(pos.Y);
		if (pos.X >= 0 && pos.X < row.size())
			return row.at(pos.X);
	}
	return m_wall;
}

Tile::Type Field::typeAt(const irr::core::vector2di &pos)
{
	return at(pos).getType();
}

std::vector<std::vector<Tile::Type>> Field::genField(void)
{
	std::vector<std::vector<Tile::Type>> res;
	size_t h = 11;
	size_t w = 21;
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
			for (auto &a : air)
				if (a == p)
					isAir = true;
			if (!isAir) {
				if ((j & 1) && (i & 1))
					type = Tile::Type::Wall;
				else
					type = Tile::Type::Box;
			}
			row.emplace_back(type);
		}
		res.emplace_back(row);
	}
	return res;
}

std::vector<std::vector<std::reference_wrapper<Tile>>> Field::genTiles(void)
{
	std::vector<std::vector<std::reference_wrapper<Tile>>> res;

	auto field = genField();
	for (size_t i = 0; i < field.size(); i++) {
		auto &field_row = field.at(i);
		std::vector<std::reference_wrapper<Tile>> row;
		for (size_t j = 0; j < field_row.size(); j++)
			row.emplace_back(add<Tile>(field_row.at(j), irr::core::vector2di(j, i)));
		res.emplace_back(row);
	}
	return res;
}

}