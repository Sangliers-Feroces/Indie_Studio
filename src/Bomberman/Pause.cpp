/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Pause
*/

#include "Pause.hpp"

namespace Bomberman {

Pause::Pause(void) :
	m_background(add<Image>(session.driver.getTexture("res/GUI/pause_background.png"), irr::core::position2d<irr::s32>(500, 50))),
	m_resume(add<Button>(irr::core::rect<irr::s32>(550, 250, 1050, 350), L"")),
	m_save(add<Button>(irr::core::rect<irr::s32>(550, 400, 1050, 500), L"")),
	m_menu(add<Button>(irr::core::rect<irr::s32>(550, 550, 1050, 650), L"")),
	m_leave(add<Button>(irr::core::rect<irr::s32>(550, 700, 1050, 800), L""))
{

	m_resume.setImage(session.driver.getTexture("res/GUI/pause_resume.png"));
	m_resume.setUseAlphaChannel(true);
	m_resume.setIsDrawBorder(false);

	m_save.setImage(session.driver.getTexture("res/GUI/pause_save.png"));
	m_save.setUseAlphaChannel(true);
	m_save.setIsDrawBorder(false);

	m_menu.setImage(session.driver.getTexture("res/GUI/pause_menu.png"));
	m_menu.setUseAlphaChannel(true);
	m_menu.setIsDrawBorder(false);

	m_leave.setImage(session.driver.getTexture("res/GUI/pause_exit.png"));
	m_leave.setUseAlphaChannel(true);
	m_leave.setIsDrawBorder(false);
	bind(session.events.gui.button_pressed, [this](auto gui) {
		if (m_resume == gui.Caller)
			session.resume_Pause = true;
		if (m_save == gui.Caller)
			session.save_game = true;
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