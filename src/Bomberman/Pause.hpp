/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Pause
*/

#pragma once

#include "Engine/EntityGuiWorld.hpp"
#include "ui/uiComponent.hpp"

namespace Bomberman {

class Pause : public en::EntityGuiWorld {
public:
	Pause(void);
	~Pause(void);
private:
	Button &m_resume;
	Button &m_save;
	Button &m_menu;
	Button &m_leave;
};

}