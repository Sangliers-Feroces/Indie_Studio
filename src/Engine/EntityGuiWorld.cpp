#include "EntityGuiWorld.hpp"

namespace Engine {
EntityGuiWorld::EntityGuiWorld(void):
		EntityGui(EntityGui::Context(*this, nullptr), getStack().top().get().m_irr_env),
		session(getStack().top()),
		m_env(session.m_irr_env)
{
}

EntityGuiWorld::~EntityGuiWorld(void)
{
}

std::stack<std::reference_wrapper<Session>>& EntityGuiWorld::getStack(void)
{
	static thread_local std::stack<std::reference_wrapper<Session>> res;

	return res;
}


EntityGuiWorld::Events::Events(void)
{
}

EntityGuiWorld::Events::~Events(void)
{
}

void EntityGuiWorld::Events::updateObserver(void)
{
	update.updateObserver();
}

EntityGuiWorld::Events::Update::Update(void)
{
}

EntityGuiWorld::Events::Update::~Update(void)
{
}

void EntityGuiWorld::Events::Update::updateObserver(void)
{
	auto now = std::chrono::high_resolution_clock::now();
	double res = std::chrono::duration<double>(now - m_time_before).count();
	m_time_before = now;
	newEvent(res);
}

}