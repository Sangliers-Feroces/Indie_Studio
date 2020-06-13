/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CheckBox
*/

#pragma once

#include "Engine/ui/GuiCheckBox.hpp"

namespace Bomberman {

class CheckBox : public en::GuiCheckBox {
	public:
		CheckBox(bool checked, const irr::core::rect<irr::s32> rectangle, const wchar_t *text = 0);
		~CheckBox(void);
};

}