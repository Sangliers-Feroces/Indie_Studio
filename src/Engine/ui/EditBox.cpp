/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EditBox
*/

#include "EditBox.hpp"

namespace Engine {

GuiEditBox::GuiEditBox(const wchar_t *text, const irr::core::rect<irr::s32> rectangle, bool border) :
	EntityGui::IGUIElementDerived<irr::gui::IGUIEditBox>([&text, &rectangle, border](auto &env, auto parent) {
		return env.addEditBox(text, rectangle, border, parent);
	})
{
}

GuiEditBox::~GuiEditBox(void)
{
}

void GuiEditBox::enableOverrideColor(bool enable)
{
	m_irr_elem_der.enableOverrideColor(enable);
}

void GuiEditBox::setDrawBorder(bool border)
{
	m_irr_elem_der.setDrawBorder(border);
}

void GuiEditBox::setMax(irr::u32 max)
{
	m_irr_elem_der.setMax(max);
}

void GuiEditBox::setMultiLine(bool enable)
{
	m_irr_elem_der.setMultiLine(enable);
}

void GuiEditBox::setOverrideColor(irr::video::SColor color)
{
	m_irr_elem_der.setOverrideColor(color);
}

void GuiEditBox::setOverrideFont(irr::gui::IGUIFont *font)
{
	m_irr_elem_der.setOverrideFont(font);
}

}