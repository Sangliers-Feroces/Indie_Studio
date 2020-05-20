#pragma once

#include <stack>
#include "Entity.hpp"

namespace Engine {

class Session;

class World : public Entity
{
public:
	World(void);
	virtual ~World(void) override = 0;

private:
	friend Session;
	static std::stack<std::reference_wrapper<irr::IrrlichtDevice>>& getStack(void);
	irr::IrrlichtDevice &m_irr_device;

public:
	irr::video::IVideoDriver &driver;
	irr::scene::IAnimatedMesh& getMesh(const std::string &path);

private:
	friend Entity;

	irr::scene::ISceneManager &m_irr_scene;
};

}