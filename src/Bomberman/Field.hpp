#pragma once

#include <vector>
#include "Engine/World.hpp"
#include "Tile.hpp"
#include "Camera.hpp"

namespace Bomberman {

class Player;

class Field : public en::World
{
public:
	Field(void);
	~Field(void);

	Tile& at(const irr::core::vector2di &pos);
	Tile::Type typeAt(const irr::core::vector2di &pos);
	void nuke(const irr::core::vector2di &pos);

	template <class MobType, typename ...Args>
	MobType& addMob(Args &&...args);

	size_t getWidth(void) const;
	size_t getHeight(void) const;

private:
	std::vector<std::vector<std::reference_wrapper<Tile>>> m_tiles;
	size_t m_w;
	size_t m_h;
	Camera &m_camera;
	Tile &m_wall;

	static std::vector<std::vector<Tile::Type>> genField(void);
	std::vector<std::vector<std::reference_wrapper<Tile>>> genTiles(void);
};

}

#include "Player.hpp"

template <class MobType, typename ...Args>
MobType& Bomberman::Field::addMob(Args &&...args)
{
	auto &s = Mob::getStack();

	s.emplace(*this);
	auto &res = add<MobType>(std::forward<Args>(args)...);
	s.pop();
	return res;
}