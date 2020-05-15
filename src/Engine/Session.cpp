#include "Session.hpp"

namespace Engine {

Session::Session(void) :
	m_irr_device(irr::createDevice(irr::video::EDT_OPENGL,
	irr::core::dimension2d<irr::u32>(1600, 900), 32, false, false, true, 0)),
	m_irr_driver(*m_irr_device->getVideoDriver()),
	m_irr_scene(*m_irr_device->getSceneManager())
{
}

Session::~Session(void)
{
}

void Session::run(void)
{
	while (m_irr_device->run()) {
		m_irr_driver.beginScene(true, true, irr::video::SColor(255,0,0,0));
		m_irr_scene.drawAll();
		m_irr_driver.endScene();
	}
}

}