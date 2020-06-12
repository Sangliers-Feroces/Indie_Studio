/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EditBox
*/

#include "EditBox.hpp"

namespace Bomberman {

EditBox::EditBox(const wchar_t *text, const irr::core::rect<irr::s32> rectangle, bool border) :
	GuiEditBox(text, rectangle, border)
{
}

EditBox::~EditBox()
{
}

}