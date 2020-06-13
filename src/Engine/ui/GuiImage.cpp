/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GuiImage
*/

#include "GuiImage.hpp"

namespace Engine {

GuiImage::GuiImage(irr::video::ITexture *image, irr::core::position2d<irr::s32> pos, bool useAlphaChannel, const wchar_t *text) :
	EntityGui::IGUIElementDerived<irr::gui::IGUIImage>([&image, &pos, &useAlphaChannel, &text](auto &env, auto parent){
		return env.addImage(image, pos, useAlphaChannel, parent, -1, text);
	})
{
}

GuiImage::~GuiImage()
{
}

void GuiImage::setImage(irr::video::ITexture *image) const
{
	m_irr_elem_der.setImage(image);
}

}