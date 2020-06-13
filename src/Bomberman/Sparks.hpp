#pragma once

#include "Mob.hpp"

namespace Bomberman {

class Sparks : public Mob
{
public:
	Sparks(const irr::core::vector2di &pos);
	void write(std::ostream &o) override;
	~Sparks(void);

	void simulate(void);
	bool stillDeadly(void);

private:
	double m_time_bef_death;

	double getRatio(void);

	static double life;
};

}