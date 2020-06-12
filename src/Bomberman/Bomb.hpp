#pragma once

#include "Mob.hpp"

namespace Bomberman {

class Bomb : public Mob
{
public:
	Bomb(const irr::core::vector2di &pos, size_t radius);
	~Bomb(void);

private:
	double m_time_bef_expl;
	size_t m_radius;

	static double explosion_delay;

	void nuke(void);
	void nukeLine(const irr::core::vector2di &pos, const irr::core::vector2di &dir, size_t max, size_t penetration = 1);
};

}