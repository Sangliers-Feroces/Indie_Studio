#include "IrrReceiver.hpp"
#include <iostream>

namespace Engine {
namespace Event {

IrrReceiver::IrrReceiver(void)
{
}

IrrReceiver::~IrrReceiver(void)
{
}

bool IrrReceiver::OnEvent(const irr::SEvent& event)
{
	key.newEvent(event);
	gui.newEvent(event);
	return false;
}

IrrReceiver::Key::Key(void)
{
}

IrrReceiver::Key::~Key(void)
{
}

IrrReceiver::Key::extract_type IrrReceiver::Key::extract(const IrrReceiver::Key::src_type &src)
{
	if (src.EventType == irr::EET_KEY_INPUT_EVENT) {
		auto &k = src.KeyInput;
		auto prev = m_state[k.Key];
		m_state[k.Key] = k.PressedDown;
		if (!prev && m_state[k.Key])
			pressed.newEvent(k.Key);
		if (prev && !m_state[k.Key])
			released.newEvent(k.Key);
		return src.KeyInput;
	} else
		return std::nullopt;
}

bool IrrReceiver::Key::getState(irr::EKEY_CODE code) const
{
	return m_state[code];
}

IrrReceiver::Key::KeyEvent::KeyEvent(void)
{
}

IrrReceiver::Key::KeyEvent::~KeyEvent(void)
{
}


IrrReceiver::Gui::Gui(void)
{
}

IrrReceiver::Gui::~Gui(void)
{
}

IrrReceiver::Gui::extract_type IrrReceiver::Gui::extract(const IrrReceiver::Gui::src_type &src)
{
	if (src.EventType == irr::EET_GUI_EVENT) {
		switch (src.GUIEvent.EventType) {
			case irr::gui::EGET_BUTTON_CLICKED:
				button_pressed.newEvent(src.GUIEvent);
				break;
			case irr::gui::EGET_CHECKBOX_CHANGED:
				checkbox_pressed.newEvent(src.GUIEvent);
				break;
			case irr::gui::EGET_LISTBOX_CHANGED:
				listbox_modified.newEvent(src.GUIEvent);
				break;
			default:
				break;
		}
		return src.GUIEvent;
	} else
		return std::nullopt;
}

IrrReceiver::Gui::GuiEvent::GuiEvent(void)
{
}

IrrReceiver::Gui::GuiEvent::~GuiEvent(void)
{
}

}
}