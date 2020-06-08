#pragma once

#include <vector>
#include "Engine/World.hpp"
#include "Tile.hpp"
#include "Camera.hpp"
#include "Player.hpp"

namespace Bomberman {

class Field : public en::World
{
public:
	Field(void);
	~Field(void);

	Tile& at(const irr::core::vector2di &pos);
	Tile::Type typeAt(const irr::core::vector2di &pos);

private:
	std::vector<std::vector<std::reference_wrapper<Tile>>> m_tiles;
	size_t m_w;
	size_t m_h;
	Camera &m_camera;
	Player &m_player;
	Tile &m_wall;

	static std::vector<std::vector<Tile::Type>> genField(void);
	std::vector<std::vector<std::reference_wrapper<Tile>>> genTiles(void);
};

}