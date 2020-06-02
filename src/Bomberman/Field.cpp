#include "Field.hpp"

#include <iostream>

namespace Bomberman {

Field::Field(void) :
	m_camera(add<en::CameraFPS>()),
	m_player(add<Player>())
{
	bind(m_player.pressedZ, [](){
		std::cout << "Player pressed Z!!" << std::endl;
	});

	bind(m_player.message, [](const std::string &msg){
		std::cout << "Player messages you!!: " << msg << std::endl;
	});

	bind(m_player.do_quit, [](){
		std::cout << "Player wants to quit!!" << std::endl;
		std::cout << "(someone please add a method in Session to break game loop)" << std::endl;
	});
}

Field::~Field(void)
{
}

}