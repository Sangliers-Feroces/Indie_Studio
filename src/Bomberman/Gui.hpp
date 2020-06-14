/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Gui
*/

#pragma once

#include "Engine/EntityGuiWorld.hpp"
#include "ui/uiComponent.hpp"
#include "Game.hpp"

namespace Bomberman {
class Gui : public en::EntityGuiWorld {
public:
	Gui(std::vector<Field::PlayerMeta> &players);
	~Gui(void);
private:
	Image &m_p1;
	Image &m_p2;
	Image &m_p3;
	Image &m_p4;

	void setIcon(Image &button, size_t idx);

};

}
