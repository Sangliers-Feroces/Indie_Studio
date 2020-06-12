/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ScrollBar
*/

#include "ScrollBar.hpp"

namespace Bomberman {

ScrollBar::ScrollBar(bool horizontal, const irr::core::rect<irr::s32> rectangle) :
	GuiScrollBar(horizontal, rectangle)
{
}

ScrollBar::~ScrollBar()
{
}

}