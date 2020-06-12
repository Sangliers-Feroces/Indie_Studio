/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ScrollBar
*/

#pragma once

#include "Engine/ui/GuiScrollBar.hpp"

namespace Bomberman {

class ScrollBar : public en::GuiScrollBar {
	public:
		ScrollBar(bool horizontal, const irr::core::rect<irr::s32> rectangle);
		~ScrollBar(void);
};

}