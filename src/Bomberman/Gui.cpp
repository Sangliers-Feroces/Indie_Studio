/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Gui
*/

#include "Gui.hpp"

namespace Bomberman {

Gui::Gui() :
	m_button(add<en::GuiButton>(irr::core::rect<irr::s32>()))
{
}

Gui::~Gui()
{
}

}