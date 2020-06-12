/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Gui
*/

#pragma once

#include "Engine/EntityGuiWorld.hpp"
#include "Engine/ui/GuiButton.hpp"
#include "Engine/Session.hpp"

namespace Bomberman {
class Gui : public en::EntityGuiWorld {
public:
	Gui(void);
	~Gui(void);
private:
	en::GuiButton &m_button;
	en::GuiButton &m_button2;
};

}
