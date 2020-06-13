/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IGOptions
*/

#include "IGOptions.hpp"

namespace Bomberman {

Options::Options(void) : 
	m_background(add<Image>(session.driver.getTexture("res/GUI/menu_background.png"), irr::core::position2d<irr::s32>(0, 0))),
	m_back(add<Button>(irr::core::rect<irr::s32>(0, 800, 100, 900), L"Back")),
	m_fscreen(add<CheckBox>(false, irr::core::rect<irr::s32>(1200, 300, 1400, 400), L"Full Screen")),
	m_mute(add<CheckBox>(false, irr::core::rect<irr::s32>(1200, 500, 1400, 600), L"Mute")),
	m_volup(add<Button>(irr::core::rect<irr::s32>(1200, 700, 1400, 800), L"+")),
	m_vol(add<StaticText>(L"50", irr::core::rect<irr::s32>(1000, 700, 1200, 800))),
	m_voldown(add<Button>(irr::core::rect<irr::s32>(800, 700, 1000, 800), L"-"))
{
	bind(session.events.gui.button_pressed, [&](auto gui) {
		if (m_back == gui.Caller)
			session.switch_Menu = true;
	});
}

Options::~Options(void)
{
}

}