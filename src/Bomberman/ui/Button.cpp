/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Button
*/

#include "Button.hpp"

namespace Bomberman {

Button::Button(irr::core::rect<irr::s32> pos, const wchar_t *text, const wchar_t *tooltiptext) :
	GuiButton(pos, text, tooltiptext)
{
}

Button::~Button()
{
}

}