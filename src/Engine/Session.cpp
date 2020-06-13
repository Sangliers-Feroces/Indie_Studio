#include "Session.hpp"
#include <iostream>

namespace Engine {

Session::Session(void) :
	m_irr_device(irr::createDevice(irr::video::EDT_OPENGL,
	irr::core::dimension2d<irr::u32>(1600, 900), 32, false, false, true, &events)),
	driver(*m_irr_device->getVideoDriver()),
	m_irr_scene(*m_irr_device->getSceneManager()),
	m_irr_env(util::ptr_to_ref(m_irr_device->getGUIEnvironment())),
	m_sound_buffer_cache([](const std::string &soundPath, sf::SoundBuffer &buffer){
		buffer.loadFromFile(soundPath);
	})
{
}

Session::~Session(void)
{
}

void Session::closeDevice(void)
{
	std::cerr << "Session Closed" << std::endl;
	m_irr_device->closeDevice();
}

void Session::run(void)
{
	while (m_irr_device->run() && !isDone()) {
		for (auto &w : m_worlds) {
			w.events.updateObserver();
			w.collectGarbage();
		}
		for (auto &gw : m_gui_worlds)
			gw.events.updateObserver();
		events.update.updateObserver();
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

double Session::rand(void)
{
	return static_cast<double>(m_rand_gen()) / static_cast<double>(std::numeric_limits<decltype(m_rand_gen())>::max());
}

size_t Session::randInt(size_t max)
{
	return m_rand_gen() % max;
}

irr::gui::IGUISkin * Session::getSkin(void)
{
	return m_irr_env.getSkin();
}

void Session::playSound(const std::string &path, double volume)
{
	m_playing_sounds.erase(std::remove_if(m_playing_sounds.begin(), m_playing_sounds.end(), [](const std::unique_ptr<sf::Sound> &sound){
		return sound->getStatus() != sf::Sound::Playing;
	}), m_playing_sounds.end());

	auto sound = new sf::Sound;
	sound->setBuffer(m_sound_buffer_cache.resolve(path));
	sound->setVolume(volume * 100);
	sound->play();
	m_playing_sounds.emplace_back(sound);
}

void Session::removeWorld(World &world)
{
	m_worlds.erase(m_worlds.find(world));
}

void Session::removeGui(EntityGuiWorld &world)
{
	m_gui_worlds.erase(m_gui_worlds.find(world));
}

}