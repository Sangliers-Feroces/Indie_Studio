#include "Bomb.hpp"
#include "Sparks.hpp"

namespace Bomberman {

Bomb::Bomb(const irr::core::vector2di &pos, size_t radius) :
	Mob("res/models/bomb.obj", "res/models/SadSteve.png"),
	m_time_bef_expl(explosion_delay),
	m_time(0.0),
	m_radius(radius),
	m_defuzed(false)
{
	setPos(pos);
	init();
}

void Bomb::init(void)
{
	setScale(irr::core::vector3df(0.0));
	bind(world.events.update, [this](auto delta){
		m_time_bef_expl -= delta;
		m_time += delta;
		setScale(irr::core::vector3df(0.5 + sin(m_time * M_PI * 3.5) * 0.1 + (1.0 / (m_time_bef_expl + 0.1) * 0.1)));
		if (m_time_bef_expl <= 0.0) {
			nuke();
			destroy();
		}
	});
}

void Bomb::write(std::ostream &o)
{
	en::util::write(o, en::util::type_id<decltype(*this)>());

	Mob::write(o);
	en::util::write(o, m_time_bef_expl);
	en::util::write(o, m_time);
	en::util::write(o, m_radius);
	en::util::write(o, m_defuzed);
}

Bomb::Bomb(std::istream &i) :
	Mob(i),
	m_time_bef_expl(en::util::read<decltype(m_time_bef_expl)>(i)),
	m_time(en::util::read<decltype(m_time)>(i)),
	m_radius(en::util::read<decltype(m_radius)>(i)),
	m_defuzed(en::util::read<decltype(m_defuzed)>(i))
{
	init();
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
		nukeLine(getPos(), d, m_radius, 1, is_simulation);
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
			if (!is_simulation)
				field.addMob<Sparks>(p);
			if (got >= penetration)
				return;
		} else if (t != Tile::Type::Air)
			return;
		if (is_simulation)
			field.nuke(p, is_simulation);
		if (!is_simulation)
			field.addMob<Sparks>(p);
	}
}

double Bomb::explosion_delay = 2.0;

}