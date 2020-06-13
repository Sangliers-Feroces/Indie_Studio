/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GuiCheckBox
*/

#include "GuiCheckBox.hpp"

namespace Engine {

GuiCheckBox::GuiCheckBox(bool checked, const irr::core::rect<irr::s32> rectangle, const wchar_t *text) :
	EntityGui::IGUIElementDerived<irr::gui::IGUICheckBox>([&checked, &rectangle, &text](auto &env, auto parent){
		return env.addCheckBox(checked, rectangle, parent, -1, text);
	})
{
}

GuiCheckBox::~GuiCheckBox(void)
{
}

bool GuiCheckBox::isChecked(void) const
{
	return m_irr_elem_der.isChecked();
}

void GuiCheckBox::setChecked(bool checked)
{
	m_irr_elem_der.setChecked(checked);
}

}