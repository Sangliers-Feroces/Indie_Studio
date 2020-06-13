#include "Sparks.hpp"

namespace Bomberman {

Sparks::Sparks(const irr::core::vector2di &pos) :
	Mob("res/models/box.obj", "res/models/SadSteve.png"),
	m_time_bef_death(life)
{
	setPos(pos);
	setScale(irr::core::vector3df(0.5));
	bind(world.events.update, [this](auto delta){
		m_time_bef_death -= delta;
		double ratio = getRatio();
		setScale(irr::core::vector3df(ratio * 0.5));
		if (stillDeadly())
			for (auto &m : field.at(getPos()).getMobs()) {
				auto &mob = m.get();
				try {
					auto &player = dynamic_cast<Player&>(mob);
					player.hitByBomb();
				} catch (const std::bad_cast&) {}
			}
		if (m_time_bef_death <= 0.0)
			destroy();
	});
}

Sparks::~Sparks(void)
{
}

void Sparks::write(std::ostream &o)
{
	en::util::write(o, en::util::type_id<decltype(*this)>());
	Mob::write(o);
	en::util::write(o, m_time_bef_death);
}

void Sparks::simulate(void)
{
	if (stillDeadly())
		field.nuke(getPos(), true);
}

bool Sparks::stillDeadly(void)
{
	return getRatio() > 0.35;
}

double Sparks::getRatio(void)
{
	return m_time_bef_death / life;
}

double Sparks::life = 1.0;

}