/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GuiStaticText
*/

#include "GuiStaticText.hpp"

namespace Engine {

GuiStaticText::GuiStaticText(const wchar_t *text, const irr::core::rect<irr::s32> rectangle, bool border, bool wordWrap, bool fillBackGround) :
	EntityGui::IGUIElementDerived<irr::gui::IGUIStaticText>([&text, &rectangle, &border, &wordWrap, &fillBackGround](auto &env, auto parent){
		return env.addStaticText(text, rectangle, border, wordWrap, parent, -1 ,fillBackGround);
	})
{
}

GuiStaticText::~GuiStaticText()
{
}

void GuiStaticText::enableOverrideColor(bool enable)
{
	m_irr_elem_der.enableOverrideColor(enable);
}

void GuiStaticText::setBackgroundColor(irr::video::SColor color)
{
	m_irr_elem_der.setBackgroundColor(color);
}

void GuiStaticText::setDrawBackground(bool draw)
{
	m_irr_elem_der.setDrawBackground(draw);
}

void GuiStaticText::setDrawBorder(bool draw)
{
	m_irr_elem_der.setDrawBorder(draw);
}

void GuiStaticText::setOverrideColor(irr::video::SColor color)
{
	m_irr_elem_der.setOverrideColor(color);
}

void GuiStaticText::setOverrideFont(irr::gui::IGUIFont *font)
{
	m_irr_elem_der.setOverrideFont(font);
}

void GuiStaticText::setText(const wchar_t *text)
{
	m_irr_elem_der.setText(text);
}

}
