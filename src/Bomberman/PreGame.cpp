/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PreGame
*/

#include "PreGame.hpp"
#include <iostream>

namespace Bomberman {

PreGame::PreGame(void) :
	m_background(add<Image>(session.driver.getTexture("res/GUI/menu_background.png"), irr::core::position2d<irr::s32>(0, 0))),
	m_back(add<Button>(irr::core::rect<irr::s32>(0, 0, 100, 100), L"Back"))
{
	bind(session.events.gui.button_pressed, [this](auto gui) {
		if (m_back == gui.Caller) {
			session.switch_Game.emit();
		}
	});
}

PreGame::~PreGame(void)
{
}

}
