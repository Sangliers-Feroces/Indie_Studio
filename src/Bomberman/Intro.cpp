/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Intro
*/

#include "Intro.hpp"

namespace Bomberman {

const std::vector<irr::io::path> urls = {
		{"res/GUI/intro_1.jpg"},
		{"res/GUI/intro_2.jpg"},
		{"res/GUI/intro_3.jpg"},
		{"res/GUI/intro_4.jpg"}
};

Intro::Intro(void) :
	m_bg(add<Image>(session.driver.getTexture(urls.at(session.randInt(4))), irr::core::position2d<irr::s32>(0, 0)))
{

	bind(session.events.key.pressed, [&](auto key) {
		if (key == irr::KEY_SPACE) {
			session.playSound("res/sounds/ui_start.ogg", 2);
			session.switch_Menu = true;
		}
	});
}

Intro::~Intro(void)
{
}

}
