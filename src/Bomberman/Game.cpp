#include "Game.hpp"
#include "ui/uiSwitch.hpp"
#include <iostream>

namespace Bomberman {

Game::Game(void) :
	m_gui(addGui<Menu>()),
	m_world(nullptr),
	m_stop_run(false)
{
	/*bind(m_field.game_done, [&]{
		m_stop_run = true;
	});*/

	bind(events.update, [&](auto){
		if (switch_preGame) {
			removeGui(m_gui);
			m_gui = addGui<PreGame>();
			switch_preGame = false;
		}

		if (switch_Menu) {
			removeGui(m_gui);
			m_gui = addGui<Menu>();
			if (m_world)
				removeWorld(*m_world);
			switch_Menu = false;
		}

		if (switch_Game) {
			removeGui(m_gui);
			m_gui = addGui<Gui>();
			m_world = &add<Field>();
			switch_Game = false;
		}
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