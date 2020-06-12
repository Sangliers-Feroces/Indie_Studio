/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GuiScrollBar
*/

#include "GuiScrollBar.hpp"

namespace Engine {

GuiScrollBar::GuiScrollBar(bool horizontal, const irr::core::rect<irr::s32> rectangle) :
	EntityGui::IGUIElementDerived<irr::gui::IGUIScrollBar>([&horizontal, &rectangle](auto &env, auto parent){
		return env.addScrollBar(horizontal, rectangle, parent);
	})
{
}

GuiScrollBar::~GuiScrollBar(void)
{
}

irr::s32 GuiScrollBar::getPos(void)
{
	return m_irr_elem_der.getPos();
}

void GuiScrollBar::setLargeStep(irr::s32 step)
{
	m_irr_elem_der.setLargeStep(step);
}

void GuiScrollBar::setMax(irr::s32 max)
{
	m_irr_elem_der.setMax(max);
}

void GuiScrollBar::setMin(irr::s32 min)
{
	m_irr_elem_der.setMin(min);
}

void GuiScrollBar::setPos(irr::s32 pos)
{
	m_irr_elem_der.setPos(pos);
}

void GuiScrollBar::setSmallStep(irr::s32 step)
{
	m_irr_elem_der.setSmallStep(step);
}

}