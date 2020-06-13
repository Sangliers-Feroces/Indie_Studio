#pragma once

#include "Mob.hpp"

namespace Bomberman {

class Bomb : public Mob
{
public:
	Bomb(const irr::core::vector2di &pos, size_t radius);
	~Bomb(void);

	void nuke(bool is_simulation = false);

private:
	double m_time_bef_expl;
	size_t m_radius;

	static double explosion_delay;

	void nukeLine(const irr::core::vector2di &pos, const irr::core::vector2di &dir, size_t max, size_t penetration = 1, bool is_simulation = false);
};

}