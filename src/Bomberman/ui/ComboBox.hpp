/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ComboBox
*/

#pragma once

#include "Engine/ui/ComboBox.hpp"

namespace Bomberman {

class ComboBox : public en::GuiComboBox {
public:
	ComboBox(const irr::core::rect<irr::s32> rect);
	~ComboBox(void);
};

}