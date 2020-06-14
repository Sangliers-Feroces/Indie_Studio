/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Gui
*/

#include "Gui.hpp"
#include <iostream>

namespace Bomberman {

Gui::Gui(std::vector<Field::PlayerMeta> &players) :
	m_p1(add<Image>(session.driver.getTexture("res/GUI/Bomberman-icon-l-1.png"), irr::core::position2d<irr::s32>(0, 0))),
	m_p2(add<Image>(session.driver.getTexture("res/GUI/Bomberman-icon-l-1.png"), irr::core::position2d<irr::s32>(1344, 0))),
	m_p3(add<Image>(session.driver.getTexture("res/GUI/Bomberman-icon-l-1.png"), irr::core::position2d<irr::s32>(0, 644))),
	m_p4(add<Image>(session.driver.getTexture("res/GUI/Bomberman-icon-l-1.png"), irr::core::position2d<irr::s32>(1344, 644)))
{
	setIcon(m_p1, players.at(0).icon_idx);
	setIcon(m_p2, players.at(1).icon_idx);
	setIcon(m_p3, players.at(2).icon_idx);
	setIcon(m_p4, players.at(3).icon_idx);
}

Gui::~Gui()
{
}

void Gui::setIcon(Image &button, size_t idx)
{
	const std::vector<irr::io::path> urls = {
		{"res/GUI/Bomberman-icon-l-1.png"},
		{"res/GUI/Bomberman-icon-l-2.png"},
		{"res/GUI/Bomberman-icon-l-3.png"},
		{"res/GUI/Bomberman-icon-l-4.png"}
	};
	button.setImage(session.driver.getTexture(urls.at(idx)));
}

}