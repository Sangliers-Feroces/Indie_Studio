#pragma once

#include <map>
#include "Model.hpp"

namespace Bomberman {

class Tile : public Model
{
public:
	enum class Type {
		Wall,
		Air,
		Box
	};

	Tile(Type type, const irr::core::vector2di &pos);
	~Tile(void);

	Type getType(void) const;
	void setType(Type type);

private:
	Type m_type;

	static const std::string& typeToTexture(Type type)
	{
		static const std::map<Type, std::string> table = {
			{Type::Box, "res/models/crate.jpg"},
			{Type::Wall, "res/models/wall.jpg"},
			{Type::Air, "res/models/crate.jpg"}
		};

		return table.at(type);
	}

	void renderType(void);
};

}