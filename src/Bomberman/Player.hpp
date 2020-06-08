#pragma once

#include "Mob.hpp"

namespace Bomberman {

class Player : public Mob
{
public:
	Player(size_t id);
	~Player(void);

private:
	irr::EKEY_CODE m_last_key;
	size_t m_bombs;
	double m_time_before_bomb;

	static double reload_rate;
};

}