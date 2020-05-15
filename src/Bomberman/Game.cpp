#include "Game.hpp"

namespace Bomberman {

Game::Game(void) :
	m_field(add<Field>())
{
}

Game::~Game(void)
{
}

}