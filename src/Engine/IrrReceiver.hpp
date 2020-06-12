#pragma once

#include <irrlicht/IEventReceiver.h>
#include "Event.hpp"

namespace Engine {
namespace Event {

class IrrReceiver : public irr::IEventReceiver
{
public:
	IrrReceiver(void);
	~IrrReceiver(void);

	class Key : public Dispatcher<irr::SEvent, irr::SEvent::SKeyInput>
	{
	public:
		Key(void);
		~Key(void);

		class KeyEvent : public CopyDispatcher<irr::EKEY_CODE>
		{
		public:
			KeyEvent(void);
			~KeyEvent(void);

		private:
			friend Key;
		};

		KeyEvent pressed;
		KeyEvent released;

		bool getState(irr::EKEY_CODE code) const;

	private:
		bool m_state[irr::KEY_KEY_CODES_COUNT] = {};

		friend IrrReceiver;
		extract_type extract(const src_type&) override;
	} key;

	class Gui : public Dispatcher<irr::SEvent, irr::SEvent::SGUIEvent>
	{
	public:
		Gui(void);
		~Gui(void);

		class GuiEvent : public CopyDispatcher<irr::SEvent::SGUIEvent>
		{
		public:
			GuiEvent(void);
			~GuiEvent(void);
		private:
			friend Gui;
		};

		GuiEvent button_pressed;

	private:
		friend IrrReceiver;
		extract_type extract(const src_type&) override;
	} gui;

private:
	bool OnEvent(const irr::SEvent& event) override;
};

}
}