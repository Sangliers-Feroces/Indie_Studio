#include "Player.hpp"

namespace Bomberman {

Player::Player(void)
{
	setPos(irr::core::vector3df(0, 0, 1000));
	for (size_t i = 0; i < 10; i++)
		for (size_t j = 0; j < 10; j++)
			for (size_t k = 0; k < 10; k++)
				add<Sub>(i * 1000, j * 1000, k * 1000);
}

Player::~Player(void)
{
}

}