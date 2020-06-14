/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EditBox
*/

#pragma once

#include "../EntityGui.hpp"

namespace Engine {

class GuiEditBox : public EntityGui::IGUIElementDerived<irr::gui::IGUIEditBox>
{
public:
	GuiEditBox(const wchar_t *text, const irr::core::rect<irr::s32> rectangle, bool border = true);
	~GuiEditBox(void);

	void enableOverrideColor(bool enable);

	void setDrawBorder(bool border);
	void setMax(irr::u32);
	void setMultiLine(bool enable);
	void setOverrideColor(irr::video::SColor color);
	void setOverrideFont(irr::gui::IGUIFont *font = 0);

	void setText(const wchar_t *text);
	const wchar_t *getText(void);
};
}
