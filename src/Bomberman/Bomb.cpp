#include "Bomb.hpp"
#include "Sparks.hpp"

namespace Bomberman {

Bomb::Bomb(const irr::core::vector2di &pos, size_t radius) :
	Mob("res/models/box.obj", "res/models/SadSteve.png"),
	m_time_bef_expl(explosion_delay),
	m_radius(radius)
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

void Bomb::nuke(void)
{
	static const std::vector<irr::core::vector2di> dirs = {
		{1, 0},
		{-1, 0},
		{0, 1},
		{0, -1},
	};

	for (auto &d : dirs)
		nukeLine(getPos(), d, m_radius);
}

void Bomb::nukeLine(const irr::core::vector2di &pos, const irr::core::vector2di &dir, size_t max, size_t penetration)
{
	size_t got = 0;

	for (size_t i = 0; i < max; i++) {
		auto p = pos + dir * i;
		auto t = field.typeAt(p);
		if (t == Tile::Type::Box) {
			field.nuke(p);
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