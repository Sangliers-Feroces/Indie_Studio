#include "Game.hpp"

namespace Bomberman {

Game::Game(void) :
	m_field(add<Field>()),
	m_gui(addGui<Gui>())
{
	run();
}

Game::~Game(void)
{
}

}