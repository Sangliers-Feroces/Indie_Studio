/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IGOptions
*/

#include "IGOptions.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace Bomberman {

Options::Options(void) : 
	m_background(add<Image>(session.driver.getTexture("res/GUI/option_background.png"), irr::core::position2d<irr::s32>(0, 0))),
	m_back(add<Button>(irr::core::rect<irr::s32>(0, 0, 100, 100), L"")),
	m_mute(add<Button>(irr::core::rect<irr::s32>(750, 300, 850, 400), L"")),
	m_volup(add<Button>(irr::core::rect<irr::s32>(825, 400, 875, 450), L"+")),
	m_vol(add<StaticText>(L"", irr::core::rect<irr::s32>(775, 400, 825, 450))),
	m_voldown(add<Button>(irr::core::rect<irr::s32>(725, 400, 775, 450), L"-")),
	m_diff(add<ComboBox>(irr::core::rect<irr::s32>(650, 600, 950, 700)))
{
	m_diff.addItem(L"Tiede", 0);
	m_diff.addItem(L"épicé", 1);
	m_diff.addItem(L"Brulant", 2);
	m_diff.addItem(L"Infernal", 3);
	m_diff.addItem(L"DOOOOOM", 4);
	m_diff.setSelected(session.m_options.level);

	m_back.setImage(session.driver.getTexture("res/GUI/pregame_back.png"));
	m_back.setUseAlphaChannel(true);
	m_back.setIsDrawBorder(false);

	m_mute.setImage(session.driver.getTexture("res/GUI/option_speaker.png"));
	m_mute.setUseAlphaChannel(true);
	m_mute.setIsDrawBorder(false);

	setVolume();
	bind(session.events.gui.button_pressed, [&](auto gui) {
		session.playSound("res/sounds/ui_click2.ogg", session.m_options.vol);
		if (m_back == gui.Caller)
			session.switch_Menu = true;
		if (m_mute == gui.Caller) {
			if (session.m_options.vol_mute) {
				session.m_options.vol_mute = false;
				m_mute.setImage(session.driver.getTexture("res/GUI/option_mute.png"));
				
			} else {
				session.m_options.vol_mute = true;
				m_mute.setImage(session.driver.getTexture("res/GUI/option_speaker.png"));
			}
		}
		if (m_volup == gui.Caller) {
			if ((session.m_options.vol += 10) > 100)
				session.m_options.vol = 100;
			setVolume();
		}
		if (m_voldown == gui.Caller) {
			if ((session.m_options.vol -= 10) < 0)
				session.m_options.vol = 0;
			setVolume();
		}
	});

	bind(world.session.events.gui.combo_modified, [&](auto gui) {
		session.playSound("res/sounds/ui_click1.ogg", session.m_options.vol);
		if (m_diff == gui.Caller) {
			session.m_options.level = m_diff.getSelected();
		}
	});

	bind(world.session.events.key.pressed, [&](auto key){
		if (key == irr::KEY_ESCAPE)
			session.switch_Menu = true;
	});
}

Options::~Options(void)
{
}

void Options::setVolume(void)
{
	irr::core::stringw str = L"";
	str += (int)session.m_options.vol;
	m_vol.setText(str.c_str());
	world.session.volumeChanged();
}
}