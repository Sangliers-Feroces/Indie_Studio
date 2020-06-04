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

World::Events::Events(void)
{
}

World::Events::~Events(void)
{
}

void World::Events::updateObserver(void)
{
	update.updateObserver();
}

World::Events::Update::Update(void)
{
}

World::Events::Update::~Update(void)
{
}

void World::Events::Update::updateObserver(void)
{
	auto now = std::chrono::high_resolution_clock::now();
	double res = std::chrono::duration<double>(now - m_time_before).count();
	m_time_before = now;
	newEvent(res);
}

}