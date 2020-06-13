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
	m_back(add<Button>(irr::core::rect<irr::s32>(0, 0, 100, 100), L"Back")),
	m_play(add<Button>(irr::core::rect<irr::s32>(900, 0, 1000, 100), L"Play")),
	m_p1(add<CheckBox>(true, irr::core::rect<irr::s32>(100, 400, 200, 500), L"Player1")),
	m_p2(add<CheckBox>(false, irr::core::rect<irr::s32>(300, 400, 400, 500), L"Player2")),
	m_p3(add<CheckBox>(false, irr::core::rect<irr::s32>(500, 400, 600, 500), L"Player3")),
	m_p4(add<CheckBox>(false, irr::core::rect<irr::s32>(700, 400, 800, 500), L"Player4")),
	m_maps(add<ComboBox>(irr::core::rect<irr::s32>(700, 600, 800, 800)))
{
	m_maps.addItem(L"Map1");
	m_maps.addItem(L"Map2");
	m_maps.addItem(L"Map3");
	m_maps.addItem(L"Map4");
	bind(session.events.gui.button_pressed, [this](auto gui) {
		if (m_back == gui.Caller) {
			session.switch_Menu.emit();
		}
		if (m_play == gui.Caller)
			session.switch_Game.emit();
	});
}

PreGame::~PreGame(void)
{
}

}
