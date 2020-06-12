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

	Tile(Type type, const irr::core::vector2di &pos);
	~Tile(void);

	Type getType(void) const;
	void setType(Type type);
	const std::vector<std::reference_wrapper<Mob>>& getMobs(void);

private:
	Type m_type;
	std::vector<std::reference_wrapper<Mob>> m_mobs;	// mobs on that tile

	static const std::string& typeToTexture(Type type, Field::Env env)
	{
		static const std::map<Field::Env, std::map<Type, std::string>> table = {
			{Field::Env::Overworld, {
				{Type::Box, "res/models/crate.jpg"},
				{Type::Wall, "res/models/wall.jpg"},
				{Type::Air, "res/models/crate.jpg"},
				{Type::Ground, "res/models/grass.jpg"}
			}}, {Field::Env::Mario, {
				{Type::Box, "res/models/crate.jpg"},
				{Type::Wall, "res/models/wall.jpg"},
				{Type::Air, "res/models/crate.jpg"},
				{Type::Ground, "res/models/grass.jpg"}
			}}
		};

		return table.at(env).at(type);
	}

	void renderType(void);
	friend Mob;
	void addMob(Mob &mob);
	void removeMob(Mob &mob);
	bool tryRemoveMob(Mob &mob);
};

}

#include "Mob.hpp"