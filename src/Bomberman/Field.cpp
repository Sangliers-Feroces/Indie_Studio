#include "Field.hpp"

namespace Bomberman {

Field::Field(void) :
	m_camera(add<en::Camera>()),
	m_player(add<Player>())
{
}

Field::~Field(void)
{
}

}