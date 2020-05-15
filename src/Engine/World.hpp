#pragma once

#include "Entity.hpp"

namespace Engine {

class World : public Entity
{
public:
	World(irr::IrrlichtDevice &device);
	virtual ~World(void) override = 0;

private:
	irr::IrrlichtDevice &m_irr_device;

public:
	irr::video::IVideoDriver &driver;

private:
	irr::scene::ISceneManager &m_irr_scene;
};

}