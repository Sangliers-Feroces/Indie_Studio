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

		class Pressed : public CopyDispatcher<irr::SEvent::SKeyInput, bool>
		{
		public:
			Pressed(void);
			~Pressed(void);

		private:
			friend Key;
			extract_type extract(const src_type&) override;
		} pressed;

		bool getState(irr::EKEY_CODE code) const;

	private:
		bool m_state[irr::KEY_KEY_CODES_COUNT] = {};

		friend IrrReceiver;
		extract_type extract(const src_type&) override;
	} key;

private:
	bool OnEvent(const irr::SEvent& event) override;
};

}
}