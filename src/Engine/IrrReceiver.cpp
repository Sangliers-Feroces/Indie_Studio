#include "IrrReceiver.hpp"

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
		m_state[k.Key] = k.PressedDown;
		return src.KeyInput;
	} else
		return std::nullopt;
}

bool IrrReceiver::Key::getState(irr::EKEY_CODE code) const
{
	return m_state[code];
}

IrrReceiver::Key::Pressed::Pressed(void)
{
}

IrrReceiver::Key::Pressed::~Pressed(void)
{
}

IrrReceiver::Key::Pressed::extract_type IrrReceiver::Key::Pressed::extract(const IrrReceiver::Key::Pressed::src_type&)
{
	return true;
}

}
}