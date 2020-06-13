#pragma once

#include <random>
#include <SFML/Audio.hpp>
#include "World.hpp"
#include "EntityGuiWorld.hpp"
#include "IrrReceiver.hpp"
#include "util.hpp"
#include "Bomberman/ui/uiSwitch.hpp"

namespace Engine {

class Session : public Bindings::Dependency::Socket
{
public:
	struct IGOptions {
		bool vol_mute;
		double vol;
		bool full_screen;

		int level;

		int map;
	};
	Session(void);
	virtual ~Session(void) = 0;

	IGOptions m_options;
	irr::scene::IAnimatedMesh& getMesh(const std::string &path);
	Event::IrrReceiver events;

	void closeDevice(void);
	double rand(void);
	size_t randInt(size_t max);
	irr::gui::IGUISkin *getSkin(void);

	void playSound(const std::string &path, double volume = 1.0);

	void reset_run(void);
	void stop_run(std::string winner);
	bool isDone(void);
	std::string getWinner(void);

	bool switch_preGame = false;
	bool switch_Menu = false;
	bool switch_Game = false;
	bool switch_Pause = false;
	bool resume_Pause = false;
	bool switch_Options = false;
	bool load_game = false;

protected:
	template <class WorldType, typename ...Args>
	WorldType& add(Args &&...args)
	{
		auto &s = World::getStack();

		s.emplace(*this);
		auto &res = m_worlds.emplace<WorldType>(std::forward<Args>(args)...);
		s.pop();
		return res;
	}
	void removeWorld(World &world);

	template<class WorldType, typename ...Args>
	WorldType& addGui(Args &&...args)
	{
		auto &s = EntityGuiWorld::getStack();

		s.emplace(*this);
		auto &res = m_gui_worlds.emplace<WorldType>(std::forward<Args>(args)...);
		s.pop();
		return res;
	}
	void removeGui(EntityGuiWorld &world);

	void run(void);

private:

	friend World;
	friend EntityGuiWorld;
	util::irr_shared<irr::IrrlichtDevice> m_irr_device;

public:
	irr::video::IVideoDriver &driver;

private:
	irr::scene::ISceneManager &m_irr_scene;
	irr::gui::IGUIEnvironment &m_irr_env;
	util::unique_set<World> m_worlds;
	util::unique_set<EntityGuiWorld> m_gui_worlds;
	std::mt19937_64 m_rand_gen;
	util::cache<std::string, sf::SoundBuffer> m_sound_buffer_cache;
	std::vector<std::unique_ptr<sf::Sound>> m_playing_sounds;

	bool m_stop_run;
	std::string m_winner;
	//temp
public:
	irr::gui::IGUIFont *m_font;
};

}