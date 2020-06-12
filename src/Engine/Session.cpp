#include "Session.hpp"

namespace Engine {

Session::Session(void) :
	m_irr_device(irr::createDevice(irr::video::EDT_OPENGL,
	irr::core::dimension2d<irr::u32>(1600, 900), 32, false, false, true, &events)),
	driver(*m_irr_device->getVideoDriver()),
	m_irr_scene(*m_irr_device->getSceneManager()),
	m_sound_buffer_cache([](const std::string &soundPath, sf::SoundBuffer &buffer){
		if (!buffer.loadFromFile(soundPath))
			throw std::invalid_argument("Can't open sound");
	})
{
}

Session::~Session(void)
{
}

void Session::run(void)
{
	while (m_irr_device->run() && !isDone()) {
		for (auto &w : m_worlds) {
			w.events.updateObserver();
			w.collectGarbage();
		}
		driver.beginScene(true, true, irr::video::SColor(255,0,0,0));
		m_irr_scene.drawAll();
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

}