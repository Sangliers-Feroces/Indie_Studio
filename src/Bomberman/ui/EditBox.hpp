/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EditBox
*/

#pragma once

#include "Engine/ui/EditBox.hpp"

namespace Bomberman {

class EditBox : public en::GuiEditBox {
public:
	EditBox(const wchar_t *text, const irr::core::rect<irr::s32> rectangle, bool border = true);
	~EditBox(void);
};

}