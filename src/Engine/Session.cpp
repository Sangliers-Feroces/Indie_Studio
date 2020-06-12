#include "Session.hpp"

namespace Engine {

Session::Session(void) :
	m_irr_device(irr::createDevice(irr::video::EDT_OPENGL,
	irr::core::dimension2d<irr::u32>(1600, 900), 32, false, false, true, &events)),
	driver(*m_irr_device->getVideoDriver()),
	m_irr_scene(*m_irr_device->getSceneManager()),
	m_irr_env(util::ptr_to_ref(m_irr_device->getGUIEnvironment()))
{
}

Session::~Session(void)
{
}

void Session::run(void)
{
	while (m_irr_device->run()) {
		for (auto &w : m_worlds)
			w.events.updateObserver();
		for (auto &gw : m_gui_worlds)
			gw.events.updateObserver();
		driver.beginScene(true, true, irr::video::SColor(255,0,0,0));
		m_irr_scene.drawAll();
		m_irr_env.drawAll();
		driver.endScene();
	}
}

irr::scene::IAnimatedMesh& Session::getMesh(const std::string &path)
{
	return util::ptr_to_ref(m_irr_scene.getMesh(path.c_str()));
}

}