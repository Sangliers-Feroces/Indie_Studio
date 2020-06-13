/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PreGame
*/

#include "PreGame.hpp"
#include <iostream>

namespace Bomberman {

PreGame::PreGame(std::vector<Field::PlayerMeta> &players) :
	m_background(add<Image>(session.driver.getTexture("res/GUI/menu_background.png"), irr::core::position2d<irr::s32>(0, 0))),
	m_back(add<Button>(irr::core::rect<irr::s32>(0, 800, 100, 900), L"Back")),
	m_play(add<Button>(irr::core::rect<irr::s32>(1500, 800, 1600, 900), L"Play")),
	m_p1(add<CheckBox>(true, irr::core::rect<irr::s32>(100, 700, 300, 800), L"Player1")),
	m_p2(add<CheckBox>(false, irr::core::rect<irr::s32>(500, 700, 700, 800), L"Player2")),
	m_p3(add<CheckBox>(false, irr::core::rect<irr::s32>(900, 700, 1100, 800), L"Player3")),
	m_p4(add<CheckBox>(false, irr::core::rect<irr::s32>(1300, 700, 1500, 800), L"Player4")),
	m_maps(add<ComboBox>(irr::core::rect<irr::s32>(700, 600, 900, 620)))
{
	m_maps.addItem(L"Map1");
	m_maps.addItem(L"Map2");
	m_maps.addItem(L"Map3");
	m_maps.addItem(L"Map4");
	bind(session.events.gui.button_pressed, [this, &players](auto gui) {
		if (m_back == gui.Caller) {
			session.switch_Menu = true;
		}
		if (m_play == gui.Caller) {
			(m_p1.isChecked()) ? players.push_back({true, "Player1"}) : players.push_back({false, "Bot1"});
			(m_p2.isChecked()) ? players.push_back({true, "Player2"}) : players.push_back({false, "Bot2"});
			(m_p3.isChecked()) ? players.push_back({true, "Player3"}) : players.push_back({false, "Bot3"});
			(m_p4.isChecked()) ? players.push_back({true, "Player4"}) : players.push_back({false, "Bot4"});
			session.switch_Game = true;
		}
	});
}

PreGame::~PreGame(void)
{
}

}
