#include "Tile.hpp"

namespace Bomberman {

Tile::Tile(Type type, const irr::core::vector2di &pos) :
	Model("res/models/box.obj", typeToTexture(type)),
	m_type(type)
{
	auto npos = pos;

	setPos(irr::core::vector3df(npos.X, 0.0, npos.Y));
	setScale(irr::core::vector3df(0.5));
	if (type == Type::Air)
		setScale(irr::core::vector3df(0.0));
}

Tile::~Tile(void)
{
}

Tile::Type Tile::getType(void) const
{
	return m_type;
}

}