#pragma once

#include "Mob.hpp"

namespace Bomberman {

class Sparks : public Mob
{
public:
	Sparks(const irr::core::vector2di &pos);
	~Sparks(void);

	void simulate(void);

private:
	double m_time_bef_death;

	bool stillDeadly(void);
	double getRatio(void);

	static double life;
};

}