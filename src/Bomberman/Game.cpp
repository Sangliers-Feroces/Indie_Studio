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
			m_world = nullptr;
			switch_Menu = false;
		}

		if (switch_Game) {
			removeGui(m_gui);
			m_gui = addGui<Gui>();
			m_world = &add<Field>(std::vector<Field::PlayerMeta>({{true, ""}, {true, ""}, {true, ""}, {true, ""}}));
			switch_Game = false;
		}

		if (switch_Pause) {
			removeGui(m_gui);
			m_gui = addGui<Pause>();
			m_world->events.update.setScale(0);
			switch_Pause = false;
		}

		if (resume_Pause) {
			removeGui(m_gui);
			m_gui = addGui<Gui>();
			m_world->events.update.setScale(1);
			resume_Pause = false;
		}

		if (switch_Options) {
			removeGui(m_gui);
			m_gui = addGui<Options>();
			switch_Options = false;
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