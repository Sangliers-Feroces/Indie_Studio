#include "Field.hpp"

namespace Bomberman {

Field::Field(irr::IrrlichtDevice &device) :
	World(device),
	m_player(add<Player>())
{
}

Field::~Field(void)
{
}

}