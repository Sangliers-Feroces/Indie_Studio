/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GuiStaticText
*/

#pragma once

#include "../EntityGui.hpp"

namespace Engine {

class GuiStaticText : public EntityGui::IGUIElementDerived<irr::gui::IGUIStaticText>
{
public:
	GuiStaticText(const wchar_t *text, const irr::core::rect<irr::s32> rectangle, bool border = false, bool wordWrap = true, bool fillBackGround = false);
	~GuiStaticText(void);

	void enableOverrideColor(bool enable);

	void setBackgroundColor(irr::video::SColor color);
	void setDrawBackground(bool draw);
	void setDrawBorder(bool draw);
	void setOverrideColor(irr::video::SColor color);
	void setOverrideFont(irr::gui::IGUIFont *font);
	void setText(const wchar_t *text);
};

}