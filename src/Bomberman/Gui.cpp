/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Gui
*/

#include "Gui.hpp"
#include <iostream>

namespace Bomberman {

static int64_t off_x = 40;
static int64_t off_y = 20;

Gui::Gui(std::vector<Field::PlayerMeta> &players) :
	m_p1((
	add<Image>(session.driver.getTexture("res/GUI/underlay_tl.png"), irr::core::position2d<irr::s32>(0, 115)),
	add<Image>(session.driver.getTexture("res/GUI/underlay_tr.png"), irr::core::position2d<irr::s32>(1600 - 200, 115)),
	add<Image>(session.driver.getTexture("res/GUI/underlay_bl.png"), irr::core::position2d<irr::s32>(0, 900 - 185)),
	add<Image>(session.driver.getTexture("res/GUI/underlay_br.png"), irr::core::position2d<irr::s32>(1600 - 200, 900 - 185)),

	add<Image>(session.driver.getTexture("res/GUI/Bomberman-icon-l-1.png"), irr::core::position2d<irr::s32>(off_x, off_y)))),
	m_p2(add<Image>(session.driver.getTexture("res/GUI/Bomberman-icon-l-1.png"), irr::core::position2d<irr::s32>(1475 - off_x, off_y))),
	m_p3(add<Image>(session.driver.getTexture("res/GUI/Bomberman-icon-l-1.png"), irr::core::position2d<irr::s32>(off_x, 775 - off_y))),
	m_p4(add<Image>(session.driver.getTexture("res/GUI/Bomberman-icon-l-1.png"), irr::core::position2d<irr::s32>(1475 - off_x, 775 - off_y))),
	m_t1(add<StaticText>(L"", irr::core::rect<irr::s32>(off_x, 135 + off_y, 200, 200))),
	m_t2(add<StaticText>(L"", irr::core::rect<irr::s32>(1510 - off_x, 135 + off_y, 1600, 200))),
	m_t3(add<StaticText>(L"", irr::core::rect<irr::s32>(off_x,  750 - off_y, 200, 775))),
	m_t4(add<StaticText>(L"", irr::core::rect<irr::s32>(1510 - off_x, 750 - off_y, 1600, 775)))
{
	setName(m_t1, players.at(0).name);
	setName(m_t2, players.at(1).name);
	setName(m_t3, players.at(2).name);
	setName(m_t4, players.at(3).name);

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

void Gui::setName(StaticText &box, const std::string& src)
{
	irr::core::stringw str = L"";
	str += src.c_str();
	box.setText(str.c_str());
}

}