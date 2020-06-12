#include <algorithm>
#include "Tile.hpp"

namespace Bomberman {

Tile::Tile(Type type, const irr::core::vector2di &pos, Field &field) :
	m_field(field),
	Model("res/models/box.obj", field.typeToTexture(type)),
	m_type(type)
{
	auto npos = pos;

	setPos(irr::core::vector3df(npos.X, type == Type::Ground ? -1.0 : 0.0, npos.Y));
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

const std::vector<std::reference_wrapper<Mob>>& Tile::getMobs(void)
{
	return m_mobs;
}

void Tile::addMob(Mob &mob)
{
	removeMob(mob);
	m_mobs.emplace_back(mob);
}

void Tile::removeMob(Mob &mob)
{
	while (tryRemoveMob(mob));
}

bool Tile::tryRemoveMob(Mob &mob)
{
	for (auto it = m_mobs.begin(); it != m_mobs.end(); it++)
		if (&it->get() == &mob) {
			m_mobs.erase(it);
			return true;
		}
	return false;
}

void Tile::renderType(void)
{
	setMaterialTexture(0, world.session.driver.getTexture(m_field.typeToTexture(m_type).c_str()));
	if (m_type == Type::Air)
		setScale(irr::core::vector3df(0.0));
	else
		setScale(irr::core::vector3df(0.5));
}

}