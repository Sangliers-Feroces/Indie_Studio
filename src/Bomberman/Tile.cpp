#include <algorithm>
#include "Tile.hpp"

namespace Bomberman {

Tile::Tile(Type type, const irr::core::vector2di &pos) :
	Model("res/models/box.obj", typeToTexture(type)),
	m_type(type),
	m_pos(pos)
{
	auto npos = pos;

	setPos(irr::core::vector3df(npos.X, 0.0, npos.Y));
	renderType();
}

Tile::Tile(std::istream &i, Type type) :
	Tile(type, en::util::read<irr::core::vector2di>(i))
{
}

Tile::Tile(std::istream &i) :
	Tile(i, en::util::read<Type>(i))
{
}

Tile::~Tile(void)
{
}

void Tile::write(std::ostream &o)
{
	en::util::write(o, m_type);
	en::util::write(o, m_pos);
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
	setMaterialTexture(0, world.session.driver.getTexture(typeToTexture(m_type).c_str()));
	if (m_type == Type::Air)
		setScale(irr::core::vector3df(0.0));
	else
		setScale(irr::core::vector3df(0.5));
}

}