#pragma once

#include "Mob.hpp"

namespace Bomberman {

class Bomb : public Mob
{
public:
	Bomb(const irr::core::vector2di &pos);
	~Bomb(void);

private:
	double m_time_bef_expl;

	static double explosion_delay;

	void nuke(void);
	void nukeLine(const irr::core::vector2di &pos, const irr::core::vector2di &dir, size_t max, size_t penetration = 1);
};

}