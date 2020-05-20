#include "Field.hpp"

namespace Bomberman {

Field::Field(void) :
	m_camera(add<en::CameraFPS>()),
	m_player(add<Player>())
{
}

Field::~Field(void)
{
}

}