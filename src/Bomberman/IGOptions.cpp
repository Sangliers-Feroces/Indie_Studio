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
	m_background(add<Image>(session.driver.getTexture("res/GUI/menu_background.png"), irr::core::position2d<irr::s32>(0, 0))),
	m_back(add<Button>(irr::core::rect<irr::s32>(0, 800, 100, 900), L"Back")),
	m_fscreen(add<CheckBox>(session.m_options.full_screen, irr::core::rect<irr::s32>(1200, 300, 1400, 400), L"Full Screen")),
	m_mute(add<CheckBox>(session.m_options.vol_mute, irr::core::rect<irr::s32>(1200, 500, 1400, 600), L"Mute")),
	m_volup(add<Button>(irr::core::rect<irr::s32>(1200, 700, 1400, 800), L"+")),
	m_vol(add<StaticText>(L"", irr::core::rect<irr::s32>(1000, 700, 1200, 800))),
	m_voldown(add<Button>(irr::core::rect<irr::s32>(800, 700, 1000, 800), L"-"))
{
	setVolume();
	bind(session.events.gui.button_pressed, [&](auto gui) {
		if (m_back == gui.Caller)
			session.switch_Menu = true;
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

	bind(session.events.gui.checkbox_pressed, [&](auto gui) {
		if (m_fscreen == gui.Caller)
			session.m_options.full_screen = m_fscreen.isChecked();
		if (m_mute == gui.Caller)
			session.m_options.vol_mute = m_mute.isChecked();
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
}
}