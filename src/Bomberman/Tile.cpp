#include <algorithm>
#include "Tile.hpp"
#include "Bomb.hpp"
#include "Sparks.hpp"
#include "PowerUp/BombUp.hpp"
#include "PowerUp/FireUp.hpp"
#include "PowerUp/PassUp.hpp"
#include "PowerUp/SpeedUp.hpp"

namespace Bomberman {

Tile::Tile(Type type, const irr::core::vector2di &pos, Field &field, int32_t height) :
	Model("res/models/box.obj", field.typeToTexture(type)),
	m_field(field),
	m_type(type),
	m_pos(pos),
	m_height(height)
{
	auto npos = pos;

	setPos(irr::core::vector3df(npos.X, m_height, npos.Y));
	renderType();
}

void Tile::write(std::ostream &o)
{
	en::util::write(o, m_type);
	en::util::write(o, m_pos);
	en::util::write(o, m_height);
	en::util::write(o, m_mobs.size());
	for (auto &m : m_mobs)
		m.get().write(o);
}

template <typename First, typename ...Args>
void Tile::genReadersImpl(Tile::reader_table &res)
{
	res.emplace(en::util::type_id<First>(), [](std::istream &i, Field &f) -> auto& {
		return f.addMob<First>(i);
	});

	if constexpr (!std::is_same_v<std::tuple<Args...>, std::tuple<>>)
		genReadersImpl<Args...>(res);
}

Tile::Tile(std::istream &i, const irr::core::vector2di &pos, Field &field, Type type) :
	Tile(type, pos, field, en::util::read<int32_t>(i))
{
	static const auto ctors = genReaders<Player, Bomb, Sparks, PowerUp::BombUp, PowerUp::FireUp, PowerUp::PassUp, PowerUp::SpeedUp>();

	auto size = en::util::read<size_t>(i);

	for (size_t it = 0; it < size; it++) {
		auto id = en::util::read<en::util::type_id_t>(i);

		m_mobs.emplace_back(ctors.at(id)(i, field));
	}
}

Tile::Tile(std::istream &i, Field &field, Type type) :
	Tile(i, en::util::read<irr::core::vector2di>(i), field, type)
{
}

Tile::Tile(std::istream &i, Field &field) :
	Tile(i, field, en::util::read<Type>(i))
{
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
		setScale(irr::core::vector3df(1.0));
}

}