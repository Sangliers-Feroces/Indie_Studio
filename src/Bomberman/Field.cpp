#include "Field.hpp"

namespace Bomberman {

Field::Field(void) :
	m_player(add<Player>())
{
}

Field::~Field(void)
{
}

}