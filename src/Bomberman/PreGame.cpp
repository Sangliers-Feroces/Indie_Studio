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
	m_back(add<Button>(irr::core::rect<irr::s32>(0, 0, 100, 100), L"")),
	m_load(add<Button>(irr::core::rect<irr::s32>(1500, 0, 1600, 100), L"")),
	m_play(add<Button>(irr::core::rect<irr::s32>(685, 800, 925, 875), L"")),
	m_p1(add<CheckBox>(true, irr::core::rect<irr::s32>(145, 660, 270, 760), L"Human ?")),
	m_p2(add<CheckBox>(false, irr::core::rect<irr::s32>(535, 660, 660, 760), L"Human ?")),
	m_p3(add<CheckBox>(false, irr::core::rect<irr::s32>(945, 660, 1070, 760), L"Human ?")),
	m_p4(add<CheckBox>(false, irr::core::rect<irr::s32>(1335, 660, 1460, 760), L"Human ?")),
	m_e1(add<EditBox>(L"", irr::core::rect<irr::s32>(170, 560, 270, 580), false)),
	m_e2(add<EditBox>(L"", irr::core::rect<irr::s32>(550, 560, 660, 580), false)),
	m_e3(add<EditBox>(L"", irr::core::rect<irr::s32>(970, 560, 1070, 580), false)),
	m_e4(add<EditBox>(L"", irr::core::rect<irr::s32>(1350, 560, 1460, 580), false)),
	m_b1(add<Button>(irr::core::rect<irr::s32>(190, 610, 240, 660), L"")),
	m_b2(add<Button>(irr::core::rect<irr::s32>(570, 610, 620, 660), L"")),
	m_b3(add<Button>(irr::core::rect<irr::s32>(990, 610, 1040, 660), L"")),
	m_b4(add<Button>(irr::core::rect<irr::s32>(1370, 610, 1420, 660), L"")),
	m_map_pre(add<Image>(session.driver.getTexture("res/GUI/map1.jpg"), irr::core::position2d<irr::s32>(406, 43))),
	m_maps(add<ComboBox>(irr::core::rect<irr::s32>(650, 370, 900, 420)))
{

	m_back.setImage(session.driver.getTexture("res/GUI/pregame_back.png"));
	m_back.setUseAlphaChannel(true);
	m_back.setIsDrawBorder(false);
	m_load.setImage(session.driver.getTexture("res/GUI/pregame_upload.png"));
	m_load.setUseAlphaChannel(true);
	m_load.setIsDrawBorder(false);
	m_play.setImage(session.driver.getTexture("res/GUI/pregame_play.png"));
	m_play.setUseAlphaChannel(true);
	m_play.setIsDrawBorder(false);

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

	m_maps.addItem(L"Grassland", 0);
	m_maps.addItem(L"Mario", 1);
	m_maps.addItem(L"Beach", 2);
	m_maps.addItem(L"DOOOOOOM", 3);
	m_maps.addItem(L"Sky heaven", 4);
	m_maps.addItem(L"Volcano", 5);
	m_maps.setSelected(session.m_options.map);
	setMap();

	bind(session.events.gui.button_pressed, [this, &players](auto gui) {
		session.playSound("res/sounds/ui_click2.ogg", session.m_options.vol);
		if (m_back == gui.Caller) {
			session.switch_Menu = true;
		}
		if (m_play == gui.Caller) {
			session.switch_Game = true;
		}
		if (m_load == gui.Caller)
			session.load_game = true;

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

	bind(session.events.gui.combo_modified, [&](auto gui) {
		session.playSound("res/sounds/ui_click1.ogg", session.m_options.vol);
		setMap();
		session.m_options.map = m_maps.getSelected();
	});

	bind(session.events.gui.checkbox_pressed, [&](auto gui) {
		session.playSound("res/sounds/ui_click1.ogg", session.m_options.vol);
		if (m_p1 == gui.Caller)
			players.at(0).is_bot = !m_p1.isChecked();
		if (m_p2 == gui.Caller) {
			players.at(1).is_bot = !m_p2.isChecked();
			//std::cout << players.at(1).is_bot << std::endl;
		}
		if (m_p3 == gui.Caller)
			players.at(2).is_bot = !m_p3.isChecked();
		if (m_p4 == gui.Caller)
			players.at(3).is_bot = !m_p4.isChecked();
	});

	bind(world.session.events.key.pressed, [&](auto key){
		if (key == irr::KEY_ESCAPE)
			session.switch_Menu = true;
	});
}

PreGame::~PreGame(void)
{
}

void PreGame::setMap(void)
{
	const std::vector<irr::io::path> urls = {
		{"res/GUI/map1.jpg"},
		{"res/GUI/map2.jpg"},
		{"res/GUI/map3.jpg"},
		{"res/GUI/map4.jpg"},
		{"res/GUI/map5.jpg"},
		{"res/GUI/map6.jpg"}
	};
	m_map_pre.setImage(session.driver.getTexture(urls.at(m_maps.getSelected())));
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
