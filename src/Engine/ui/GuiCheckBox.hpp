/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GuiCheckBox
*/

#pragma once

#include "../EntityGui.hpp"

namespace Engine {

class GuiCheckBox : public EntityGui::IGUIElementDerived<irr::gui::IGUICheckBox>
{
public:
	GuiCheckBox(bool checked, const irr::core::rect<irr::s32> rectangle, const wchar_t *text = 0);
	~GuiCheckBox(void);

	bool isChecked(void) const;

	void setChecked(bool checked);
};

}
