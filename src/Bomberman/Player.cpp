#include "Player.hpp"

#include <iostream>

namespace Bomberman {

Player::Player(void)
{
	setPos(irr::core::vector3df(0, 0, 1000));
	for (size_t i = 0; i < 10; i++)
		for (size_t j = 0; j < 10; j++)
			for (size_t k = 0; k < 10; k++)
				add<Sub>(i * 1000, j * 1000, k * 1000);

	/*bind(world.events.update, [this](auto deltaTime) {
		std::cout << deltaTime << std::endl;
		std::cout << world.session.events.key.getState(irr::KEY_KEY_Z) << std::endl;
	});*/

	bind(world.session.events.key.pressed, [this](auto key){
		if (key == irr::EKEY_CODE::KEY_KEY_Z)
			pressedZ.emit();
		else if (key == irr::EKEY_CODE::KEY_KEY_S)
			message.emit("fuck you");
		else if (key == irr::EKEY_CODE::KEY_ESCAPE)
			do_quit.emit();
	});
}

Player::~Player(void)
{
}

}