#pragma once

#include <irrlicht/IEventReceiver.h>
#include "Event.hpp"

namespace Engine {
namespace Event {

class IrrReceiver : public irr::IEventReceiver
{
	/*class KeyPressed : public Dispatcher<irr::SEvent, >
	{
	public:
	};*/

public:
	IrrReceiver(void);
	~IrrReceiver(void);

private:
	bool OnEvent(const irr::SEvent& event) override;
};

}
}