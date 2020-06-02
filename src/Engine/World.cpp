#include "World.hpp"

namespace Engine {

World::World(void) :
	Entity(Entity::Context(*this, nullptr), getStack().top().get().m_irr_scene),
	session(getStack().top()),
	m_irr_scene(session.m_irr_scene)
{
}

World::~World(void)
{
}

std::stack<std::reference_wrapper<Session>>& World::getStack(void)
{
	static thread_local std::stack<std::reference_wrapper<Session>> res;

	return res;
}

}