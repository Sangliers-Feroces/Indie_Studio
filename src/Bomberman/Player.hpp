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
};

}