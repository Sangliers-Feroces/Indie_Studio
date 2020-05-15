#pragma once

#include "World.hpp"
#include "util.hpp"

namespace Engine {

class Session
{
public:
	Session(void);
	virtual ~Session(void) = 0;

	void run(void);

protected:
	template <class WorldType, typename ...Args>
	WorldType& add(Args &&...args)
	{
		return m_worlds.emplace<WorldType>(m_irr_device, std::forward<Args>(args)...);
	}

private:
	util::irr_shared<irr::IrrlichtDevice> m_irr_device;
	irr::video::IVideoDriver &m_irr_driver;
	irr::scene::ISceneManager &m_irr_scene;
	util::unique_set<World> m_worlds;
};

}