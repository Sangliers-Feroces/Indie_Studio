/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Menu
*/

#include "Menu.hpp"

namespace Bomberman {

Menu::Menu(void) :
	m_background(add<Image>(session.driver.getTexture("res/GUI/menu_background.png"), irr::core::position2d<irr::s32>(0, 0))),
	m_play(add<Button>(irr::core::rect<irr::s32>(200, 400, 800, 600), L"Play")),
	m_quit(add<Button>(irr::core::rect<irr::s32>(200, 600, 800, 800), L"Quit"))
{
	bind(session.events.gui.button_pressed, [this](auto gui) {
		if (m_play == gui.Caller)
			play_game.emit(UI_PREGAME);
		if (m_quit == gui.Caller)
			session.closeDevice();
	});
	m_play.setPressedImage(session.driver.getTexture("res/GUI/menu_background.png"));
}

Menu::~Menu(void)
{
}

}