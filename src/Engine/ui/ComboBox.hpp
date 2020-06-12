/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ComboBox
*/

#pragma once

#include "../EntityGui.hpp"

namespace Engine {

class GuiComboBox : public EntityGui::IGUIElementDerived<irr::gui::IGUIComboBox>
{
public:
	GuiComboBox(irr::core::rect<irr::s32> rect);
	~GuiComboBox(void);

	irr::u32 addItem(const wchar_t *text, irr::u32 data = 0);
	void clear(void);

	irr::s32 getIndexForItemData(irr::u32 data) const;
	const wchar_t *getItem(irr::u32 idx) const;
	irr::u32 getItemCount(void) const;
	irr::u32 getitemData(irr::u32 idx) const;
	irr::s32 getSelected(void) const;
	void removeItem(irr::u32 idx);
	void setSelected(irr::s32 idx);
	void setTextAlignement(irr::gui::EGUI_ALIGNMENT horizontal, irr::gui::EGUI_ALIGNMENT vertical);
};
}