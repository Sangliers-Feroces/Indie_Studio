/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GuiImage
*/

#pragma once

#include "../EntityGui.hpp"

namespace Engine {

class GuiImage : public EntityGui::IGUIElementDerived<irr::gui::IGUIImage>
{
public:
	GuiImage(irr::video::ITexture *image, irr::core::position2d<irr::s32> pos, bool useAlphaChannel = true, const wchar_t *text = 0);
	~GuiImage(void);

	void setImage(irr::video::ITexture *image) const;
};

}