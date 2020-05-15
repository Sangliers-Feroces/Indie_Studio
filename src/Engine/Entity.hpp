#pragma once

#include <irrlicht/irrlicht.h>
#include "util.hpp"

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
	Entity(const Context &ctx, irr::scene::ISceneManager &sceneMgr);
	virtual ~Entity(void) = 0;

protected:
	World &world;

	template <class EntityType, typename ...Args>
	EntityType& add(Args &&...args)
	{
		return  m_children.emplace<EntityType>(Context(world, this), std::forward<Args>(args)...);
	}

	const irr::core::vector3df& getPos(void) const;
	const irr::core::vector3df& getRot(void) const;
	const irr::core::vector3df& getScale(void) const;

	void setPos(const irr::core::vector3df& pos);
	void setRot(const irr::core::vector3df& rot);
	void setScale(const irr::core::vector3df& scale);

private:
	Entity *m_parent;
	util::irr_shared<irr::scene::ISceneNode, true> m_irr_node;
	util::unique_set<Entity> m_children;
};

}

#include "World.hpp"

namespace en = Engine;