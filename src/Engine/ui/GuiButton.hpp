/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GuiButton
*/

#pragma once

#include "../EntityGui.hpp"

namespace Engine {

class GuiButton : public EntityGui::IGUIElementDerived<irr::gui::IGUIButton>
{
public:
	GuiButton(irr::core::rect<irr::s32> pos, const wchar_t *text=0, const wchar_t *tooltiptext=0);
	~GuiButton(void);

protected:
	irr::gui::IGUIFont *getActiveFont(void) const;
	bool isAlphaChannelUsed(void) const;
	bool isDrawingBorder(void) const;
	bool isPressed(void) const;
	bool isPushButton(void) const;
	
	void setImage(irr::video::ITexture *image);
	void setImage(irr::video::ITexture *image, irr::core::rect<irr::s32> &pos);
	void setIsPushButton(bool isPushButton);
	void setPressed(bool pressed);
	void setPressedImage(irr::video::ITexture *image);
	void setPressedImage(irr::video::ITexture *image, irr::core::rect<irr::s32> &pos);
	void setScaleImage (bool scaleImage);
	void setSprite(irr::gui::EGUI_BUTTON_STATE state, irr::s32 index, irr::video::SColor color, bool loop);
	void setSpriteBank(irr::gui::IGUISpriteBank *bank);
	void setUseAlphaChannel(bool useAlphaChannel);
};
}
