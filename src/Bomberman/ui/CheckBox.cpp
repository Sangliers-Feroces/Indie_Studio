/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CheckBox
*/

#include "CheckBox.hpp"

namespace Bomberman {

CheckBox::CheckBox(bool checked, const irr::core::rect<irr::s32> rectangle, const wchar_t *text) :
	GuiCheckBox(checked, rectangle, text)
{
}

CheckBox::~CheckBox()
{
}

}