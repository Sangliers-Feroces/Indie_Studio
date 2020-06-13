#include <algorithm>
#include "Tile.hpp"
#include "Bomb.hpp"
#include "Sparks.hpp"

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

Tile::Tile(std::istream &i, Field &field, Type type) :
	Tile(type, en::util::read<irr::core::vector2di>(i))
{
	static const std::map<en::util::type_id_t, std::function<Mob& (std::istream&, Field&)>> ctors = {
		{en::util::type_id<Player>(), [](std::istream &i, Field &f) -> auto& {
			return f.addMob<Player>(i);
		}},
		{en::util::type_id<Bomb>(), [](std::istream &i, Field &f) -> auto& {
			return f.addMob<Bomb>(i);
		}},
		{en::util::type_id<Sparks>(), [](std::istream &i, Field &f) -> auto& {
			return f.addMob<Sparks>(i);
		}}
	};

	auto size = en::util::read<size_t>(i);

	for (size_t it = 0; it < size; it++) {
		auto id = en::util::read<en::util::type_id_t>(i);

		m_mobs.emplace_back(ctors.at(id)(i, field));
	}
}

Tile::Tile(std::istream &i, Field &field) :
	Tile(i, field, en::util::read<Type>(i))
{
}

Tile::~Tile(void)
{
}

void Tile::write(std::ostream &o)
{
	en::util::write(o, m_type);
	en::util::write(o, m_pos);
	en::util::write(o, m_mobs.size());
	for (auto &m : m_mobs)
		m.get().write(o);
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