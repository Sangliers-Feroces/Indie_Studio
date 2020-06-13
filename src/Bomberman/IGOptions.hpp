/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Options
*/

#pragma once

#include "Engine/EntityGuiWorld.hpp"
#include "ui/uiComponent.hpp"
#include "Game.hpp"

namespace Bomberman {

class Options : public en::EntityGuiWorld {
public:
	Options(void);
	~Options(void);
protected:
	Image &m_background;
	Button &m_back;

	CheckBox &m_fscreen;

	CheckBox &m_mute;
	Button &m_volup;
	StaticText &m_vol;
	Button &m_voldown;

private:
	void setVolume(void);
};

}
