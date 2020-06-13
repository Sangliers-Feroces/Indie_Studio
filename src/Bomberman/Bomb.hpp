#pragma once

#include "Mob.hpp"

namespace Bomberman {

class Bomb : public Mob
{
public:
	Bomb(const irr::core::vector2di &pos, size_t radius);
	void init(void);
	void write(std::ostream &o) override;
	Bomb(std::istream &i);
	~Bomb(void);

	void nuke(bool is_simulation = false);
	void defuze(void);

private:
	double m_time_bef_expl;
	size_t m_radius;
	bool m_defuzed;

	static double explosion_delay;

	void nukeLine(const irr::core::vector2di &pos, const irr::core::vector2di &dir, size_t max, size_t penetration = 1, bool is_simulation = false);
};

}