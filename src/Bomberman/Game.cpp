#include "Game.hpp"
#include "ui/uiSwitch.hpp"
#include <iostream>

namespace Bomberman {

Game::Game(void) :
	m_menu(addGui<Menu>()),
	m_stop_run(false)
{
	/*bind(m_field.game_done, [&]{
		m_stop_run = true;
	});*/
	bind(m_menu.play_game, [&](ui_switch_t ui_switch){
		std::cerr << ui_switch << std::endl;
	});
	run();
}

Game::~Game(void)
{
}

bool Game::isDone(void) const
{
	return m_stop_run;
}

}