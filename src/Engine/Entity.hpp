#pragma once

#include <irrlicht/irrlicht.h>
#include <stack>
#include <functional>
#include "Event.hpp"
#include "util.hpp"

namespace Engine {

class World;

class Entity : public Bindings::Dependency::Socket
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

	Entity(void);
	Entity(const Context &ctx, irr::scene::ISceneManager &sceneMgr);

protected:
	Entity(irr::scene::ISceneNode *irrnode);	// Node has been built by the sub class
	static World& getStackWorld(void);
	static irr::scene::ISceneManager& getStackScene(void);
	static irr::scene::ISceneNode* getStackParentNode(void);

public:
	virtual ~Entity(void) = 0;

	template <class ISceneNodeType>
	class ISceneNodeDerivedBase;
	template <class ISceneNodeType>
	class ISceneNodeDerived;

protected:
	World &world;

	template <class EntityType, typename ...Args>
	EntityType& add(Args &&...args)
	{
		getStack().emplace(world, this);
		auto &res = m_children.emplace<EntityType>(std::forward<Args>(args)...);
		getStack().pop();
		return res;
	}

	void destroy(void);

	const irr::core::vector3df& getPos(void) const;
	const irr::core::vector3df& getRot(void) const;
	const irr::core::vector3df& getScale(void) const;

	void setPos(const irr::core::vector3df& pos);
	void setRot(const irr::core::vector3df& rot);
	void setScale(const irr::core::vector3df& scale);

	const irr::video::SMaterial& getMaterial(const irr::u32& num);
	const irr::u32 getMaterialCount() const;

	void setMaterialFlag(irr::video::E_MATERIAL_FLAG flag, bool newvalue);
	void setMaterialTexture(irr::u32 textureLayer, irr::video::ITexture *texture);
	void setMaterialType(irr::video::E_MATERIAL_TYPE newtype);

private:
	static std::stack<Context>& getStack(void);
	Entity *m_parent;
	util::irr_shared<irr::scene::ISceneNode, true> m_irr_node;
	util::unique_set<Entity> m_children;
};

template <class ISceneNodeType>
class Entity::ISceneNodeDerivedBase : public Entity
{
public:
	ISceneNodeDerivedBase(ISceneNodeType *node) :
		Entity(node),
		m_irr_node_der(util::ptr_to_ref(node))
	{
	}

	~ISceneNodeDerivedBase(void) override
	{
	}

protected:
	ISceneNodeType &m_irr_node_der;
};

template <class ISceneNodeType>
class Entity::ISceneNodeDerived : public Entity::ISceneNodeDerivedBase<ISceneNodeType>
{
public:
	ISceneNodeDerived(const std::function<ISceneNodeType* (irr::scene::ISceneManager &scene, irr::scene::ISceneNode *parent)> &factory) :
		Entity::ISceneNodeDerivedBase<ISceneNodeType>(factory(getStackScene(), getStackParentNode()))
	{
	}

	~ISceneNodeDerived(void) override
	{
	}
};

}

#include "World.hpp"

namespace en = Engine;