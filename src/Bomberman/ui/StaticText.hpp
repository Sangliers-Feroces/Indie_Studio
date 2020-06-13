/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** StaticText
*/

#pragma once

#include "Engine/ui/GuiStaticText.hpp"

namespace Bomberman {

class StaticText : public en::GuiStaticText {
	public:
		StaticText(const wchar_t *text, const irr::core::rect<irr::s32> rectangle, bool border = false, bool wordWrap = true, bool fillBackGround = false);
		~StaticText(void);
};

}