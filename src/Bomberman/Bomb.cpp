#include "Bomb.hpp"
#include "Sparks.hpp"

namespace Bomberman {

Bomb::Bomb(const irr::core::vector2di &pos, size_t radius) :
	Mob("res/models/box.obj", "res/models/SadSteve.png"),
	m_time_bef_expl(explosion_delay),
	m_radius(radius),
	m_defuzed(false)
{
	setPos(pos);
	setScale(irr::core::vector3df(0.3));
	bind(world.events.update, [this](auto delta){
		m_time_bef_expl -= delta;
		if (m_time_bef_expl <= 0.0) {
			nuke();
			destroy();
		}
	});
}

Bomb::~Bomb(void)
{
}

void Bomb::nuke(bool is_simulation)
{
	static const std::vector<irr::core::vector2di> dirs = {
		{1, 0},
		{-1, 0},
		{0, 1},
		{0, -1},
	};

	if (m_defuzed)
		return;
	for (auto &d : dirs)
		nukeLine(getPos(), d, m_radius, is_simulation);
}

void Bomb::defuze(void)
{
	m_defuzed = true;
	setScale(irr::core::vector3df(0.0));
	destroy();
}

void Bomb::nukeLine(const irr::core::vector2di &pos, const irr::core::vector2di &dir, size_t max, size_t penetration, bool is_simulation)
{
	size_t got = 0;

	for (size_t i = 0; i < max; i++) {
		auto p = pos + dir * i;
		auto t = field.typeAt(p);
		if (t == Tile::Type::Box) {
			field.nuke(p, is_simulation);
			got++;
			field.addMob<Sparks>(p);
			if (got >= penetration)
				return;
		} else if (t != Tile::Type::Air)
			return;
		field.addMob<Sparks>(p);
	}
}

double Bomb::explosion_delay = 2.0;

}