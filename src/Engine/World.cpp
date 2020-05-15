#include "World.hpp"

namespace Engine {

World::World(irr::IrrlichtDevice &device) :
	Entity(Entity::Context(*this, nullptr)),
	m_irr_device(device),
	driver(*device.getVideoDriver()),
	m_irr_scene(*device.getSceneManager())
{
}

World::~World(void)
{
}

}