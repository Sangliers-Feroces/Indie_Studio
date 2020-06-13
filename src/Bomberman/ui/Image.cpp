/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Image
*/

#include "Image.hpp"

namespace Bomberman {

Image::Image(irr::video::ITexture *image, irr::core::position2d<irr::s32> pos, bool useAlphaChannel, const wchar_t *text) :
	GuiImage(image, pos, useAlphaChannel, text)
{
}

Image::~Image()
{
}

}