#include "Sparks.hpp"

namespace Bomberman {

Sparks::Sparks(const irr::core::vector2di &pos) :
	Mob("res/models/box.obj", "res/models/SadSteve.png"),
	m_time_bef_death(life)
{
	setPos(pos);
	setScale(irr::core::vector3df(0.5));
	bind(world.events.update, [this](auto delta){
		setScale(irr::core::vector3df((m_time_bef_death / life) * 0.5));
		m_time_bef_death -= delta;
		if (m_time_bef_death <= 0.0)
			destroy();
	});
}

Sparks::~Sparks(void)
{
}

double Sparks::life = 1.0;

}