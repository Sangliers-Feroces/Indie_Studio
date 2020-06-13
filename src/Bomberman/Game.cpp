#include "Game.hpp"
#include "ui/uiSwitch.hpp"
#include <fstream>
#include <iostream>

namespace Bomberman {

Game::Game(void) :
	m_gui(addGui<Menu>()),
	m_world(nullptr)
{
	bind(events.update, [&](auto) {
		if (switch_preGame) {
			removeGui(m_gui);
			m_gui = addGui<PreGame>(m_players);
			switch_preGame = false;
		}

		if (switch_Menu) {
			removeGui(m_gui);
			m_gui = addGui<Menu>();
			if (m_world)
				removeWorld(*m_world);
			m_world = nullptr;
			m_players.clear();
			switch_Menu = false;
		}

		if (switch_Game) {
			removeGui(m_gui);
			m_gui = addGui<Gui>();
			if (m_world)
				removeWorld(*m_world);
			m_world = &add<Field>(m_players);
			m_world->events.update.setScale(1);
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

		if (load_game) {
			std::ifstream save("save.BOMBS", std::ios::binary);

			if (save.good()) {
				if (m_world)
					removeWorld(*m_world);
				m_world = &add<Field>(save);
			}
			load_game = false;
		}

		if (isDone()) {
			removeGui(m_gui);
			m_gui = addGui<WinScreen>();
			m_world->events.update.setScale(0);
			reset_run();
		}
	});
	run();
}

Game::~Game(void)
{
}

}