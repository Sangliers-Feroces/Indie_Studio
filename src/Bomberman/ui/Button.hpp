/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Button
*/

#pragma once

#include "Engine/ui/GuiButton.hpp"

namespace Bomberman {

class Button : public en::GuiButton {
	public:
		Button(irr::core::rect<irr::s32> pos, const wchar_t *text=0, const wchar_t *tooltiptext=0);
		~Button(void);

	protected:
	private:
};

}
