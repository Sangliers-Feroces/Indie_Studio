/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Menu
*/

#include "Menu.hpp"

namespace Bomberman {

Menu::Menu(void) :
	m_background(add<Image>(session.driver.getTexture("res/GUI/menu_background.jpg"), irr::core::position2d<irr::s32>(0, 0))),
	m_play(add<Button>(irr::core::rect<irr::s32>(1000, 350, 1500, 500), L"")),
	m_opt(add<Button>(irr::core::rect<irr::s32>(1000, 500, 1500, 650), L"")),
	m_quit(add<Button>(irr::core::rect<irr::s32>(1000, 650, 1500, 800), L""))
{
	m_play.setImage(session.driver.getTexture("res/GUI/menu_play.png"));
	m_play.setIsDrawBorder(false);
	m_play.setUseAlphaChannel(true);

	m_opt.setImage(session.driver.getTexture("res/GUI/menu_options.png"));
	m_opt.setIsDrawBorder(false);
	m_opt.setUseAlphaChannel(true);

	m_quit.setImage(session.driver.getTexture("res/GUI/menu_exit.png"));
	m_quit.setIsDrawBorder(false);
	m_quit.setUseAlphaChannel(true);


	bind(session.events.gui.button_pressed, [this](auto gui) {
		session.playSound("res/sounds/ui_click2.ogg", session.m_options.vol);
		if (m_play == gui.Caller)
			session.switch_preGame = true;
		else if (m_quit == gui.Caller)
			session.closeDevice();
		if (m_opt == gui.Caller)
			session.switch_Options = true;
	});
	m_play.setPressedImage(session.driver.getTexture("res/GUI/menu_background.png"));
}

Menu::~Menu(void)
{
}

}