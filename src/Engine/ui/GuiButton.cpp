/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GuiButton
*/

#include "GuiButton.hpp"

namespace Engine {

GuiButton::GuiButton(irr::core::rect<irr::s32> pos, const wchar_t *text, const wchar_t *tooltiptext) :
	EntityGui::IGUIElementDerived<irr::gui::IGUIButton>([&pos, &text, &tooltiptext](auto &env, auto parent){
		return env.addButton(pos, parent, -1, text, tooltiptext);
	})
{
}

GuiButton::~GuiButton(void)
{
}

irr::gui::IGUIFont *GuiButton::getActiveFont(void) const
{
	return m_irr_elem_der.getActiveFont();
}

bool GuiButton::isAlphaChannelUsed(void) const
{
	return m_irr_elem_der.isAlphaChannelUsed();
}

bool GuiButton::GuiButton::isDrawingBorder(void) const
{
	return m_irr_elem_der.isDrawingBorder();
}

bool GuiButton::isPressed(void) const
{
	return m_irr_elem_der.isPressed();
}

bool GuiButton::isPushButton(void) const
{
	return m_irr_elem_der.isPushButton();
}

void GuiButton::setImage(irr::video::ITexture *image)
{
	m_irr_elem_der.setImage(image);
}

void GuiButton::setImage(irr::video::ITexture *image, irr::core::rect<irr::s32> &pos)
{
	m_irr_elem_der.setImage(image, pos);
}

void GuiButton::setIsPushButton(bool isPushButton)
{
	m_irr_elem_der.setIsPushButton(isPushButton);
}

void GuiButton::setPressed(bool pressed)
{
	m_irr_elem_der.setPressed(pressed);
}

void GuiButton::setPressedImage(irr::video::ITexture *image)
{
	m_irr_elem_der.setPressedImage(image);
}

void GuiButton::setPressedImage(irr::video::ITexture *image, irr::core::rect<irr::s32> &pos)
{
	m_irr_elem_der.setPressedImage(image, pos);
}

void GuiButton::setScaleImage (bool scaleImage)
{
	m_irr_elem_der.setScaleImage(scaleImage);
}

void GuiButton::setSprite(irr::gui::EGUI_BUTTON_STATE state, irr::s32 index, irr::video::SColor color, bool loop)
{
	m_irr_elem_der.setSprite(state, index, color, loop);
}

void GuiButton::setSpriteBank(irr::gui::IGUISpriteBank *bank)
{
	m_irr_elem_der.setSpriteBank(bank);
}

void GuiButton::setUseAlphaChannel(bool useAlphaChannel)
{
	m_irr_elem_der.setUseAlphaChannel(useAlphaChannel);
}

}