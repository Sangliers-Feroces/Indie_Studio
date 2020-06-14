/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PreGame
*/

#include "PreGame.hpp"
#include <iostream>

//J1 C : 135 / 660  N : 135 /  550

//j2 C 500

//j3 925

//j4 1310
namespace Bomberman {

PreGame::PreGame(std::vector<Field::PlayerMeta> &players) :
	m_background(add<Image>(session.driver.getTexture("res/GUI/pregame_background.jpg"), irr::core::position2d<irr::s32>(0, 0))),
	m_back(add<Button>(irr::core::rect<irr::s32>(0, 800, 100, 900), L"Back")),
	m_play(add<Button>(irr::core::rect<irr::s32>(1500, 800, 1600, 900), L"Play")),
	m_p1(add<CheckBox>(true, irr::core::rect<irr::s32>(170, 660, 270, 760), L"Human ?")),
	m_p2(add<CheckBox>(false, irr::core::rect<irr::s32>(560, 660, 660, 760), L"Human ?")),
	m_p3(add<CheckBox>(false, irr::core::rect<irr::s32>(970, 660, 1070, 760), L"Human ?")),
	m_p4(add<CheckBox>(false, irr::core::rect<irr::s32>(1360, 660, 1460, 760), L"Human ?")),
	m_e1(add<EditBox>(L"", irr::core::rect<irr::s32>(170, 560, 270, 580), false)),
	m_e2(add<EditBox>(L"", irr::core::rect<irr::s32>(550, 560, 660, 580), false)),
	m_e3(add<EditBox>(L"", irr::core::rect<irr::s32>(970, 560, 1070, 580), false)),
	m_e4(add<EditBox>(L"", irr::core::rect<irr::s32>(1350, 560, 1460, 580), false)),
	m_b1(add<Button>(irr::core::rect<irr::s32>(190, 610, 240, 660), L"")),
	m_b2(add<Button>(irr::core::rect<irr::s32>(570, 610, 620, 660), L"")),
	m_b3(add<Button>(irr::core::rect<irr::s32>(990, 610, 1040, 660), L"")),
	m_b4(add<Button>(irr::core::rect<irr::s32>(1370, 610, 1420, 660), L"")),
	m_maps(add<ComboBox>(irr::core::rect<irr::s32>(700, 600, 900, 620))),
	m_difficulty(add<ComboBox>(irr::core::rect<irr::s32>(700, 800, 900, 850)))
{

	m_b1.setUseAlphaChannel(true);
	m_b1.setIsDrawBorder(false);
	m_b2.setUseAlphaChannel(true);
	m_b2.setIsDrawBorder(false);
	m_b3.setUseAlphaChannel(true);
	m_b3.setIsDrawBorder(false);
	m_b4.setUseAlphaChannel(true);
	m_b4.setIsDrawBorder(false);

	setIcon(m_b1, players.at(0).icon_idx);
	setIcon(m_b2, players.at(1).icon_idx);
	setIcon(m_b3, players.at(2).icon_idx);
	setIcon(m_b4, players.at(3).icon_idx);

	m_e1.setMax(7);
	setName(m_e1, players.at(0).name);
	m_e2.setMax(7);
	setName(m_e2, players.at(1).name);
	m_e3.setMax(7);
	setName(m_e3, players.at(2).name);
	m_e4.setMax(7);
	setName(m_e4, players.at(3).name);

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
			session.switch_Game = true;
		}

		if (m_b1 == gui.Caller) {
			if (++ players.at(0).icon_idx > 3)
				players.at(0).icon_idx = 0;
			setIcon(m_b1, players.at(0).icon_idx);
		}

		if (m_b2 == gui.Caller) {
			if (++ players.at(1).icon_idx > 3)
				players.at(1).icon_idx = 0;
			setIcon(m_b2, players.at(1).icon_idx);
		}

		if (m_b3 == gui.Caller) {
			if (++ players.at(2).icon_idx > 3)
				players.at(2).icon_idx = 0;
			setIcon(m_b3, players.at(2).icon_idx);
		}

		if (m_b4 == gui.Caller) {
			if (++ players.at(3).icon_idx > 3)
				players.at(3).icon_idx = 0;
			setIcon(m_b4, players.at(3).icon_idx);
		}
	});

	bind(session.events.gui.listbox_modified, [&](auto gui) {
		if (m_difficulty == gui.Caller)
			session.m_options.level = m_difficulty.getSelected();
		if (m_maps == gui.Caller)
			session.m_options.map = m_difficulty.getSelected();
	});

	bind(session.events.gui.checkbox_pressed, [&](auto gui) {
	});
}

PreGame::~PreGame(void)
{
}

void PreGame::setIcon(Button &button, size_t idx)
{
	const std::vector<irr::io::path> urls = {
		{"res/GUI/Bomberman-icon-s-1.png"},
		{"res/GUI/Bomberman-icon-s-2.png"},
		{"res/GUI/Bomberman-icon-s-3.png"},
		{"res/GUI/Bomberman-icon-s-4.png"}
	};
	button.setImage(session.driver.getTexture(urls.at(idx)));
}

void PreGame::setName(EditBox &box, const std::string& src)
{
	irr::core::stringw str = L"";
	str += src.c_str();
	box.setText(str.c_str());
}

}
