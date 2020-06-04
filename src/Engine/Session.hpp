#pragma once

#include "World.hpp"
#include "IrrReceiver.hpp"
#include "util.hpp"

namespace Engine {

class Session
{
public:
	Session(void);
	virtual ~Session(void) = 0;

	irr::scene::IAnimatedMesh& getMesh(const std::string &path);
	Event::IrrReceiver events;

protected:
	template <class WorldType, typename ...Args>
	WorldType& add(Args &&...args)
	{
		World::getStack().emplace(*this);
		auto &res = m_worlds.emplace<WorldType>(std::forward<Args>(args)...);
		World::getStack().pop();
		return res;
	}

	void run(void);

private:
	friend World;
	util::irr_shared<irr::IrrlichtDevice> m_irr_device;

public:
	irr::video::IVideoDriver &driver;

private:
	irr::scene::ISceneManager &m_irr_scene;
	util::unique_set<World> m_worlds;
};

}