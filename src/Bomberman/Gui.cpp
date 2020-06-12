/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Gui
*/

#include "Gui.hpp"

namespace Bomberman {

Gui::Gui() :
	m_button(add<en::GuiButton>(irr::core::rect<irr::s32>(0, 0, 200, 200), L"Exit"))
{
	bind(session.events.gui.button_pressed, [this](auto gui) {
		if (m_button == gui.element)
			session.m_irr_device->closeDevice();
	});
}

Gui::~Gui()
{
}

}