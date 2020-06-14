/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WinScreen
*/

#pragma once

#include "Engine/EntityGuiWorld.hpp"
#include "ui/uiComponent.hpp"

namespace Bomberman {

class WinScreen : public en::EntityGuiWorld {
public:
	WinScreen(void);
	~WinScreen(void);
private:

	Image &m_background;
	StaticText &m_winner;
	Button &m_replay;
	Button &m_menu;
	Button &m_leave;
};

}