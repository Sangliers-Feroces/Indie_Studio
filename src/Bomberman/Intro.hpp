/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Intro
*/

#pragma once

#include "Engine/EntityGuiWorld.hpp"
#include "ui/Image.hpp"

namespace Bomberman {

class Intro : public en::EntityGuiWorld {
public:
	Intro(void);
	~Intro(void);
private:
	Image &m_bg;
};

}
