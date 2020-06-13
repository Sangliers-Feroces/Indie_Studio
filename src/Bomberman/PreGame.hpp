/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PreGame
*/

#pragma once

#include "Engine/EntityGuiWorld.hpp"
#include "ui/uiComponent.hpp"

namespace Bomberman {

class PreGame : public en::EntityGuiWorld {
public:
	PreGame(void);
	~PreGame(void);

private:
	Image &m_background;
	Button &m_back;
};

}