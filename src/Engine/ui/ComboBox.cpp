/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ComboBox
*/

#include "ComboBox.hpp"

namespace Engine {

GuiComboBox::GuiComboBox(irr::core::rect<irr::s32> rect) :
	EntityGui::IGUIElementDerived<irr::gui::IGUIComboBox>([&rect](auto &env, auto parent) {
		return env.addComboBox(rect, parent);
	})
{
}

GuiComboBox::~GuiComboBox(void)
{
}

irr::u32 GuiComboBox::addItem(const wchar_t *text, irr::u32 data)
{
	return m_irr_elem_der.addItem(text, data);
}

void GuiComboBox::clear(void)
{
	m_irr_elem_der.clear();
}

irr::s32 GuiComboBox::getIndexForItemData(irr::u32 data) const
{
	return m_irr_elem_der.getIndexForItemData(data);
}

const wchar_t *GuiComboBox::getItem(irr::u32 idx) const
{
	return m_irr_elem_der.getItem(idx);
}

irr::u32 GuiComboBox::getItemCount(void) const
{
	return m_irr_elem_der.getItemCount();
}

irr::u32 GuiComboBox::getitemData(irr::u32 idx) const
{
	return m_irr_elem_der.getItemData(idx);
}

irr::s32 GuiComboBox::getSelected(void) const
{
	return m_irr_elem_der.getSelected();
}

void GuiComboBox::removeItem(irr::u32 idx)
{
	m_irr_elem_der.removeItem(idx);
}

void GuiComboBox::setSelected(irr::s32 idx)
{
	m_irr_elem_der.setSelected(idx);
}

void GuiComboBox::setTextAlignement(irr::gui::EGUI_ALIGNMENT horizontal, irr::gui::EGUI_ALIGNMENT vertical)
{
	m_irr_elem_der.setTextAlignment(horizontal, vertical);
}

}