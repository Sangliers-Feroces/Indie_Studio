/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Menu
*/

#pragma once

#include "Engine/EntityGuiWorld.hpp"
#include "ui/uiComponent.hpp"

namespace Bomberman {

class Menu : public en::EntityGuiWorld {
public:
	Menu(void);
	~Menu(void);

private:
	Image &m_background;
	Button &m_play;
	Button &m_opt;
	Button &m_quit;
};

}