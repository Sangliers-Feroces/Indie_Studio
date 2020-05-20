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
		World::getStack().push(m_irr_device);
		auto &res = m_worlds.emplace<WorldType>(std::forward<Args>(args)...);
		World::getStack().pop();
		return res;
	}

private:
	util::irr_shared<irr::IrrlichtDevice> m_irr_device;
	irr::video::IVideoDriver &m_irr_driver;
	irr::scene::ISceneManager &m_irr_scene;
	util::unique_set<World> m_worlds;
};

}