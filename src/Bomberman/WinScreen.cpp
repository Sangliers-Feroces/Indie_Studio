/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WinScreen
*/

#include "WinScreen.hpp"

namespace Bomberman {

WinScreen::WinScreen(void) :
	m_background(add<Image>(session.driver.getTexture("res/GUI/ws_background.png"), irr::core::position2d<irr::s32>(0, 0))),
	m_winner(add<StaticText>(L"", irr::core::rect<irr::s32>(750, 500, 950, 600))),
	m_replay(add<Button>(irr::core::rect<irr::s32>(1065, 580, 1165, 680))),
	m_menu(add<Button>(irr::core::rect<irr::s32>(730, 580, 830, 680))),
	m_leave(add<Button>(irr::core::rect<irr::s32>(350, 580, 450, 680)))
{

	m_replay.setIsDrawBorder(false);
	m_replay.setUseAlphaChannel(true);
	m_replay.setImage(session.driver.getTexture("res/GUI/ws_play.png"));

	m_menu.setIsDrawBorder(false);
	m_menu.setUseAlphaChannel(true);
	m_menu.setImage(session.driver.getTexture("res/GUI/ws_home.png"));

	m_leave.setIsDrawBorder(false);
	m_leave.setUseAlphaChannel(true);
	m_leave.setImage(session.driver.getTexture("res/GUI/ws_stop.png"));

	irr::core::stringw str = L"";
	str += session.getWinner().c_str();
	m_winner.setText(str.c_str());

	bind(session.events.gui.button_pressed, [&](auto gui) {
		if (m_replay == gui.Caller) {
			session.switch_Game = true;
		}
		if (m_menu == gui.Caller) {
			session.switch_Menu = true;
		}
		if (m_leave == gui.Caller)
			session.closeDevice();
	});
}

WinScreen::~WinScreen()
{
}

}