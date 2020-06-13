/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Image
*/

#pragma once

#include "Engine/ui/GuiImage.hpp"

namespace Bomberman {

class Image : public en::GuiImage {
	public:
		Image(irr::video::ITexture *image, irr::core::position2d<irr::s32> pos, bool useAlphaChannel = true, const wchar_t *text = 0);
		~Image(void);
};

}