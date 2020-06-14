/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PreGame
*/

#pragma once

#include "Engine/EntityGuiWorld.hpp"
#include "ui/uiComponent.hpp"
#include "Game.hpp"

namespace Bomberman {

class PreGame : public en::EntityGuiWorld {
public:
	PreGame(std::vector<Field::PlayerMeta> &players);
	~PreGame(void);

private:
	Image &m_background;

	Button &m_back;
	Button &m_play;

	CheckBox &m_p1;
	CheckBox &m_p2;
	CheckBox &m_p3;
	CheckBox &m_p4;

	EditBox &m_e1;
	EditBox &m_e2;
	EditBox &m_e3;
	EditBox &m_e4;

	Button &m_b1;
	Button &m_b2;
	Button &m_b3;
	Button &m_b4;

	Image &m_map_pre;
	ComboBox &m_maps;
private:
	void setName(EditBox &box, const std::string& src);
	void setIcon(Button &button, size_t idx);
};

}