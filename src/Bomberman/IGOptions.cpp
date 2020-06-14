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
	m_background(add<Image>(session.driver.getTexture("res/GUI/menu_background.jpg"), irr::core::position2d<irr::s32>(0, 0))),
	m_back(add<Button>(irr::core::rect<irr::s32>(0, 800, 100, 900), L"Back")),
	m_volup(add<Button>(irr::core::rect<irr::s32>(1200, 700, 1400, 800), L"")),
	m_vol(add<StaticText>(L"", irr::core::rect<irr::s32>(1000, 700, 1200, 800))),
	m_voldown(add<Button>(irr::core::rect<irr::s32>(800, 700, 1000, 800), L""))
{
	m_vol.setOverrideFont(session.m_font);
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
}
}