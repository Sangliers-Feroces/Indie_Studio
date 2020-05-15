#include "Session.hpp"

namespace Engine {

Session::Session(void) :
	m_irr_device(irr::createDevice(irr::video::EDT_OPENGL,
	irr::core::dimension2d<irr::u32>(1600, 900), 32, false, false, true, 0))
{
}

Session::~Session(void)
{
}

}