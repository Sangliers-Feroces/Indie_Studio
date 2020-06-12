/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GuiScrollBar
*/

#pragma once

#include "../EntityGui.hpp"

namespace Engine {

class GuiScrollBar : public EntityGui::IGUIElementDerived<irr::gui::IGUIScrollBar>
{
public:
	GuiScrollBar(bool horizontal, const irr::core::rect<irr::s32> rectangle);
	~GuiScrollBar(void);

	irr::s32 getPos(void);

	void setLargeStep(irr::s32 step);
	void setMax(irr::s32 max);
	void setMin(irr::s32 min);
	void setPos(irr::s32 pos);
	void setSmallStep(irr::s32 step);
};

}