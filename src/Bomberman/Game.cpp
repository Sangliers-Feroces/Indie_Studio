#include "Game.hpp"

namespace Bomberman {

Game::Game(void) :
	m_field(add<Field>(std::vector<Field::PlayerMeta>({{false, ""}, {false, ""}, {true, ""}, {true, ""}}))),
	m_gui(addGui<Gui>()),
	m_stop_run(false)
{
	bind(m_field.game_done, [&]{
		m_stop_run = true;
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