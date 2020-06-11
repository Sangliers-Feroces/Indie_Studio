/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityGuiGui
*/

#include "EntityGui.hpp"
#include <iostream>

namespace Engine {

EntityGui::EntityGui(void) :
	world(getStack().top().world),
	m_parent(getStack().top().parent),
	m_irr_elem(getStackScene().getDefaultGUIElementFactory()->addGUIElement(irr::gui::EGUIET_ELEMENT, getStackParentElem()))
{
}

EntityGui::EntityGui(irr::gui::IGUIElement *irrelem) :
	world(getStack().top().world),
	m_parent(getStack().top().parent),
	m_irr_elem(irrelem)
{
}

EntityGui::EntityGui(const Context &ctx, irr::gui::IGUIEnvironment &env) :
	world(ctx.world),
	m_parent(ctx.parent),
	m_irr_elem(env.getDefaultGUIElementFactory()->addGUIElement(irr::gui::EGUIET_ROOT, m_parent ?  &*m_parent->m_irr_elem : nullptr))
{
}

EntityGui::~EntityGui(void)
{
}

std::stack<EntityGui::Context>& EntityGui::getStack(void)
{
	static thread_local std::stack<EntityGui::Context> res;

	return res;
}

EntityGuiWorld& EntityGui::getStackWorld(void)
{
	return getStack().top().world;
}

irr::gui::IGUIEnvironment& EntityGui::getStackScene(void)
{
	return getStack().top().world.m_env;
}

irr::gui::IGUIElement* EntityGui::getStackParentElem(void)
{
	auto &p = getStack().top().parent;

	if (p)
		return &*p->m_irr_elem;
	else
		return nullptr;
}

void EntityGui::destroy(void)
{
	if (m_parent == nullptr)
		throw std::runtime_error("Can't destroy root EntityGui");

	auto &c = m_parent->m_children;
	auto got = c.find(*this);
	if (got == c.end())
		throw std::runtime_error("Can't find EntityGui in its own parent");
	c.erase(got);
}

}