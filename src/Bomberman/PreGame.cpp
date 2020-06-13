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
	m_maps(add<ComboBox>(irr::core::rect<irr::s32>(700, 600, 900, 620))),
	m_difficulty(add<ComboBox>(irr::core::rect<irr::s32>(700, 800, 900, 850)))
{
	m_maps.addItem(L"Mario Map");
	m_maps.addItem(L"OverWorld Map");
	m_maps.addItem(L"Map3");
	m_maps.addItem(L"Map4");
	m_maps.addItem(L"Map5");
	m_maps.addItem(L"Map6");
	m_maps.setSelected(0);


	m_difficulty.addItem(L"LVL1", 1);
	m_difficulty.addItem(L"LVL2", 2);
	m_difficulty.addItem(L"LVL3", 3);
	m_difficulty.addItem(L"LVL4", 4);
	m_difficulty.addItem(L"LVL5", 5);
	m_difficulty.setSelected(0);

	session.m_options.level = m_difficulty.getSelected();
	bind(session.events.gui.button_pressed, [this, &players](auto gui) {
		if (m_back == gui.Caller) {
			session.switch_Menu = true;
		}
		if (m_play == gui.Caller) {
			(m_p1.isChecked()) ? players.push_back({false, "Player1"}) : players.push_back({true, "Bot1"});
			(m_p2.isChecked()) ? players.push_back({false, "Player2"}) : players.push_back({true, "Bot2"});
			(m_p3.isChecked()) ? players.push_back({false, "Player3"}) : players.push_back({true, "Bot3"});
			(m_p4.isChecked()) ? players.push_back({false, "Player4"}) : players.push_back({true, "Bot4"});
			session.switch_Game = true;
		}
	});

	bind(session.events.gui.listbox_modified, [&](auto gui) {
		if (m_difficulty == gui.Caller)
			session.m_options.level = m_difficulty.getSelected();
		if (m_maps == gui.Caller)
			session.m_options.map = m_difficulty.getSelected();
	});
}

PreGame::~PreGame(void)
{
}

}
