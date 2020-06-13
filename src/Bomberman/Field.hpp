#pragma once

#include <iostream>
#include <vector>
#include "Engine/World.hpp"
#include "Tile.hpp"
#include "Camera.hpp"

namespace Bomberman {

class Player;

class Field : public en::World
{
public:
	struct PlayerMeta {
		bool is_bot;
		std::string name;
	};

	Field(const std::vector<PlayerMeta> &players);
	std::vector<std::vector<std::reference_wrapper<Tile>>> readTiles(std::istream &i);
	Field(std::istream &i);
	~Field(void);

	en::Event::Generator<> game_done;

	Tile& at(const irr::core::vector2di &pos);
	Tile::Type typeAt(const irr::core::vector2di &pos);
	void nuke(const irr::core::vector2di &pos, bool is_simulation = false);
	void genItem(const irr::core::vector2di &pos);

	template <class MobType, typename ...Args>
	MobType& addMob(Args &&...args);

	size_t getWidth(void) const;
	size_t getHeight(void) const;

	void updateBombMap(void);
	bool isBombed(const irr::core::vector2di &pos);
	bool anySpark(const irr::core::vector2di &pos);

	std::vector<std::reference_wrapper<Player>> getPlayers(void);

	void write(std::ostream&);

private:
	std::vector<std::vector<std::reference_wrapper<Tile>>> m_tiles;
	std::vector<std::vector<bool>> m_bombs;
	size_t m_w;
	size_t m_h;
	Camera &m_camera;
	Tile &m_wall;
	size_t m_players_alive;
	std::vector<std::reference_wrapper<Player>> m_players;

	static std::string id_to_str(size_t id);
	static std::vector<std::vector<Tile::Type>> genField(void);
	std::vector<std::vector<std::reference_wrapper<Tile>>> genTiles(void);
	void addBarrier(void);
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