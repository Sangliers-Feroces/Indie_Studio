#pragma once

#include "Engine/World.hpp"
#include "Player.hpp"

namespace Bomberman {

class Field : public en::World
{
public:
	Field(irr::IrrlichtDevice &device);
	~Field(void);

private:
	Player &m_player;
};

}