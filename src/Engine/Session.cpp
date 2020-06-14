#include "Session.hpp"
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

#include <ctime>

namespace Engine {

Session::Session(void) :
	m_options({false, 100, false, 0, 0}),
	m_irr_device(irr::createDevice(irr::video::EDT_OPENGL,
	irr::core::dimension2d<irr::u32>(1600, 900), 32, false, false, true, &events)),
	driver(*m_irr_device->getVideoDriver()),
	m_irr_scene(*m_irr_device->getSceneManager()),
	m_irr_env(util::ptr_to_ref(m_irr_device->getGUIEnvironment())),
	m_rand_gen(std::time(nullptr)),
	m_sound_buffer_cache([](const std::string &soundPath, sf::SoundBuffer &buffer){
		buffer.loadFromFile(soundPath);
	}),
	m_stop_run(false),
	m_winner(""),
	m_font(m_irr_env.getFont("res/GUI/font2.png"))
{
	m_irr_env.getSkin()->setFont(m_font);
	m_irr_scene.setShadowColor(irr::video::SColor(150, 0, 0, 0));

	std::ifstream options("options.bin", std::ios::binary);

	if (options.good())
		m_options = en::util::read<decltype(m_options)>(options);
	std::cout << m_options.level << std::endl;
}

Session::~Session(void)
{
	std::ofstream options("options.bin", std::ios::trunc | std::ios::binary);

	if (options.good())
		en::util::write(options, m_options);
}

void Session::closeDevice(void)
{
	std::cerr << "Session Closed" << std::endl;
	m_irr_device->closeDevice();
}

void Session::run(void)
{
	while (m_irr_device->run()) {
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

double Session::getVolume(void) const
{
	return (m_options.vol / 100.0) * (m_options.vol_mute ? 0.0 : 1.0);
}

void Session::playSound(const std::string &path, double volume)
{
	m_playing_sounds.erase(std::remove_if(m_playing_sounds.begin(), m_playing_sounds.end(), [](const std::unique_ptr<sf::Sound> &sound){
		return sound->getStatus() != sf::Sound::Playing;
	}), m_playing_sounds.end());

	auto sound = new sf::Sound;
	sound->setBuffer(m_sound_buffer_cache.resolve(path));
	sound->setVolume(volume * 100 * getVolume());
	sound->play();
	m_playing_sounds.emplace_back(sound);
}

void Session::playSoundRnd(const std::string &path, size_t size, double volume)
{
	std::stringstream ss;

	ss << path << randInt(size) << ".ogg";
	playSound(ss.str(), volume);
}

void Session::reset_run(void)
{
	m_stop_run = false;
}

void Session::stop_run(std::string winner)
{
	m_stop_run = true;
	m_winner = winner;
}

std::string Session::getWinner(void)
{
	return m_winner;
}

bool Session::isDone(void)
{
	return m_stop_run;
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