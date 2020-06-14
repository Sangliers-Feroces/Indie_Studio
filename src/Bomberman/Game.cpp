#include "Game.hpp"
#include "ui/uiSwitch.hpp"
#include <fstream>
#include <iostream>

namespace Bomberman {

Game::Game(void) :
	m_gui(addGui<Menu>()),
	m_world(nullptr)
{
	player_reset();
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
			player_reset();
			switch_Menu = false;
		}

		if (switch_Game) {
			removeGui(m_gui);
			m_gui = addGui<Gui>(m_players);
			if (m_world)
				removeWorld(*m_world);
			m_world = &add<Field>(m_players, Field::getEnvs().at(m_options.map));
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
			m_gui = addGui<Gui>(m_players);
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
				removeGui(m_gui);
				m_gui = addGui<Gui>(m_players);
				if (m_world)
					removeWorld(*m_world);
				m_world = &add<Field>(save);
			}
			load_game = false;
		}

		if (save_game) {
			if (m_world) {
				std::ofstream save("save.BOMBS", std::ios::trunc | std::ios::binary);
				try {
					dynamic_cast<Field&>(*m_world).write(save);
				} catch (const std::bad_cast&) {}

				std::cout << "Game saved." << std::endl;
			}
			save_game = false;
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

void Game::player_reset(void)
{
	m_players.clear();
	m_players.push_back({false, genName(), 0});
	m_players.push_back({true, genName(), 1});
	m_players.push_back({true, genName(), 2});
	m_players.push_back({true, genName(), 3});

}

std::string Game::genName(void)
{
	const std::vector<std::string> names = {
		"jacob", "Frank", "Oliver", "Nabil", "David", "Tokyo",
		"Hotel", "Wiskey", "Morgan", "Gordon", "Mickey", "Yu", "Yuri"
	};
	return names.at(randInt(names.size()));
}

}