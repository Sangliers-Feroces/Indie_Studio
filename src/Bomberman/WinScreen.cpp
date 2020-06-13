/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WinScreen
*/

#include "WinScreen.hpp"

namespace Bomberman {

WinScreen::WinScreen(void) :
	m_winner(add<StaticText>(L"", irr::core::rect<irr::s32>(650, 450, 950, 600))),
	m_replay(add<Button>(irr::core::rect<irr::s32>(650, 600, 750, 700), L"Replay")),
	m_menu(add<Button>(irr::core::rect<irr::s32>(750, 600, 850, 700), L"Menu")),
	m_leave(add<Button>(irr::core::rect<irr::s32>(850, 600, 950, 700), L"Leave"))
{
	irr::core::stringw str = L"Winners is :";
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