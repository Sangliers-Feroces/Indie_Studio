/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Pause
*/

#include "Pause.hpp"

namespace Bomberman {

Pause::Pause(void) :
	m_resume(add<Button>(irr::core::rect<irr::s32>(600, 50, 1000, 250), L"Resume")),
	m_save(add<Button>(irr::core::rect<irr::s32>(600, 250, 1000, 450), L"Save")),
	m_menu(add<Button>(irr::core::rect<irr::s32>(600, 450, 1000, 650), L"Return to main menu")),
	m_leave(add<Button>(irr::core::rect<irr::s32>(600, 650, 1000, 850), L"Exit"))
{
	bind(session.events.gui.button_pressed, [this](auto gui) {
		if (m_resume == gui.Caller) {
			session.resume_Pause = true;
		}
		if (m_menu == gui.Caller)
			session.switch_Menu = true;
		if (m_leave == gui.Caller)
			session.closeDevice();
	});

	bind(world.session.events.key.pressed, [&](auto key){
		if (key == irr::KEY_ESCAPE)
			session.resume_Pause = true;
	});
}

Pause::~Pause(void)
{
}

}