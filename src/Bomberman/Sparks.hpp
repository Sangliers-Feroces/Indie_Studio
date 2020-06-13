#pragma once

#include "Mob.hpp"

namespace Bomberman {

class Sparks : public Mob
{
public:
	Sparks(const irr::core::vector2di &pos);
	void init(void);
	void write(std::ostream &o) override;
	Sparks(std::istream &i);
	~Sparks(void);

	void simulate(void);
	bool stillDeadly(void);

private:
	double m_time_bef_death;

	double getRatio(void);

	static double life;
};

}