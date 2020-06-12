/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Gui
*/

#include "Gui.hpp"
#include <iostream>

namespace Bomberman {

Gui::Gui() :
	m_button(add<en::GuiButton>(irr::core::rect<irr::s32>(0, 0, 200, 200), L"Exit")),
	m_button2(add<en::GuiButton>(irr::core::rect<irr::s32>(0, 200, 400, 400), L"TEST"))

{
	bind(session.events.gui.button_pressed, [this](auto gui) {
		if (m_button == gui.Caller)
			session.closeDevice();
		else if (m_button2 == gui.Caller) {
			std::cerr << "NON NOUNOURS" << std::endl;
		}
	});
}

Gui::~Gui()
{
}

}