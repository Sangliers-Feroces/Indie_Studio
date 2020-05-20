#include "Player.hpp"

namespace Bomberman {

Player::Player(void) :
	AnimatedMesh(getStackWorld().getMesh("res/models/dolphin.md2"))
{
}

Player::~Player(void)
{
}

}