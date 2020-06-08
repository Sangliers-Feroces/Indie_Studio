#pragma once

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif
#include <irrlicht/irrlicht.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

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

private:
	bool OnEvent(const irr::SEvent& event) override;
};

}
}