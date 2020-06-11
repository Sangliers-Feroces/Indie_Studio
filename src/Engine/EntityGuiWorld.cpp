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

}