#include "EntityGuiWorld.hpp"

namespace Engine {
EntityGuiWorld::EntityGuiWorld(void):
		EntityGui(),
		session(getStack().top()),
		m_env(util::ptr_to_ref(session.m_irr_device->getGUIEnvironment()))
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