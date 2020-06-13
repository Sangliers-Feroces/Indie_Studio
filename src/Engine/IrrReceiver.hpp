#pragma once

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif
#include <irrlicht/irrlicht.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <chrono>
#include "Event.hpp"

namespace Engine {

class Session;

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
		GuiEvent checkbox_pressed;
		GuiEvent listbox_modified;

	private:
		friend IrrReceiver;
		extract_type extract(const src_type&) override;
	} gui;

	class Update : public Event::CopyDispatcher<double>
	{
	public:
		Update(void);
		~Update(void);

	private:
		std::chrono::high_resolution_clock::time_point m_time_before;

		friend Session;
		void updateObserver(void);
	} update;

private:
	bool OnEvent(const irr::SEvent& event) override;
};

}
}