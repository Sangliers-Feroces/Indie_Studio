#include "Tile.hpp"

namespace Bomberman {

Tile::Tile(Type type, const irr::core::vector2di &pos) :
	Model("res/models/box.obj", typeToTexture(type)),
	m_type(type)
{
	auto npos = pos;

	setPos(irr::core::vector3df(npos.X, 0.0, npos.Y));
	renderType();
}

Tile::~Tile(void)
{
}

Tile::Type Tile::getType(void) const
{
	return m_type;
}

void Tile::setType(Type type)
{
	m_type = type;
	renderType();
}

void Tile::renderType(void)
{
	setMaterialTexture(0, world.session.driver.getTexture(typeToTexture(m_type).c_str()));
	if (m_type == Type::Air)
		setScale(irr::core::vector3df(0.0));
	else
		setScale(irr::core::vector3df(0.5));
}

}