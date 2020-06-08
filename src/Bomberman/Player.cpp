#include "Player.hpp"

#include <iostream>

namespace Bomberman {

Player::Player(void)
{
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