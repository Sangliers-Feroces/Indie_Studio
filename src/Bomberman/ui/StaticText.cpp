/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** StaticText
*/

#include "StaticText.hpp"

namespace Bomberman {

StaticText::StaticText(const wchar_t *text, const irr::core::rect<irr::s32> rectangle, bool border, bool wordWrap, bool fillBackGround) :
	GuiStaticText(text, rectangle, border, wordWrap, fillBackGround)
{
}

StaticText::~StaticText()
{
}

}