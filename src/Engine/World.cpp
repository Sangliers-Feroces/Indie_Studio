#include "World.hpp"

namespace Engine {

World::World(void) :
	Entity(Entity::Context(*this, nullptr), *getStack().top().get().getSceneManager()),
	m_irr_device(getStack().top()),
	driver(*getStack().top().get().getVideoDriver()),
	m_irr_scene(*getStack().top().get().getSceneManager())
{
}

World::~World(void)
{
}

std::stack<std::reference_wrapper<irr::IrrlichtDevice>>& World::getStack(void)
{
	static thread_local std::stack<std::reference_wrapper<irr::IrrlichtDevice>> res;

	return res;
}

}