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
	return false;
}

}
}