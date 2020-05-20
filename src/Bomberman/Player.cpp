#include "Player.hpp"

namespace Bomberman {

Player::Player(void) :
	AnimatedMesh("res/models/dolphin.md2")
{
	setPos(irr::core::vector3df(-10, 100, 2000));
}

Player::~Player(void)
{
}

}