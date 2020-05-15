#pragma once

#include <irrlicht/irrlicht.h>

namespace Engine {

class World;

class Entity
{
public:
	struct Context
	{
	public:
		Context(World &world, Entity *parent) : 
			world(world),
			parent(parent)
		{
		}
		~Context(void)
		{
		}
	
	private:
		friend Entity;

		World &world;
		Entity *parent;
	};

	Entity(const Context &ctx);
	virtual ~Entity(void) = 0;

private:
	//irr::scene::ISceneNode &m_irr_node;

protected:
	World &world;

private:
	Entity *m_parent;
};

}

#include "World.hpp"

namespace en = Engine;