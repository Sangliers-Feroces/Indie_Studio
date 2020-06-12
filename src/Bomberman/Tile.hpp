#pragma once

#include <map>
#include "Model.hpp"

namespace Bomberman {

class Mob;
class Field;

class Tile : public Model
{
public:
	enum class Type {
		Wall,
		Air,
		Box,
		Ground
	};

	Tile(Type type, const irr::core::vector2di &pos, Field &field);
	~Tile(void);

	Type getType(void) const;
	void setType(Type type);
	const std::vector<std::reference_wrapper<Mob>>& getMobs(void);

private:
	Type m_type;
	Field &m_field;
	std::vector<std::reference_wrapper<Mob>> m_mobs;	// mobs on that tile

	void renderType(void);
	friend Mob;
	void addMob(Mob &mob);
	void removeMob(Mob &mob);
	bool tryRemoveMob(Mob &mob);
};

}

#include "Mob.hpp"
#include "Field.hpp"