/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityGui
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include <stack>
#include <functional>
#include "Event.hpp"
#include "util.hpp"

namespace Engine {

class EntityGuiWorld;

class EntityGui : public Bindings::Dependency::Socket
{
public:
	struct Context
	{
	public:
		Context(EntityGuiWorld &world, EntityGui *parent) :
			world(world),
			parent(parent)
		{
		}
		~Context(void)
		{
		}
	private:
		friend EntityGui;

		EntityGuiWorld &world;
		EntityGui *parent;
	};

	EntityGui(void);
	EntityGui(const Context &ctx, irr::scene::ISceneManager &sceneMgr);

protected:
	EntityGui(irr::scene::ISceneNode *irrnode);
	static EntityGuiWorld& getStackWorld(void);
	static irr::scene::ISceneManager& getStackScene(void);
	static irr::scene::ISceneNode* getStackParentNode(void);

public:
	virtual ~EntityGui(void) = 0;

	template <class ISceneNodeType>
	class ISceneNodeDerivedBase;
	template <class ISceneNodeType>
	class ISceneNodeDerived;

protected:
	EntityGuiWorld &world;

	template <class EntityType, typename ...Args>
	EntityType& add(Args &&...args)
	{
		getStack().emplace(world, this);
		auto &res = m_children.emplace<EntityType>(std::forward<Args>(args)...);
		getStack().pop();
		return res;
	}

	void destroy(void);

	const irr::video::SMaterial& getMaterial(const irr::u32& num);
	const irr::u32 getMaterialCount() const;

	void setMaterialFlag(irr::video::E_MATERIAL_FLAG flag, bool newvalue);
	void setMaterialTexture(irr::u32 textureLayer, irr::video::ITexture *texture);
	void setMaterialType(irr::video::E_MATERIAL_TYPE newtype);

private:
	static std::stack<Context>& getStack(void);
	EntityGui *m_parent;
	util::irr_shared<irr::scene::ISceneNode, true> m_irr_node;
	util::unique_set<EntityGui> m_children;
};

template <class ISceneNodeType>
class EntityGui::ISceneNodeDerivedBase : public EntityGui
{
public:
	ISceneNodeDerivedBase(ISceneNodeType *node) :
		EntityGui(node),
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
class EntityGui::ISceneNodeDerived : public EntityGui::ISceneNodeDerivedBase<ISceneNodeType>
{
public:
	ISceneNodeDerived(const std::function<ISceneNodeType* (irr::scene::ISceneManager &scene, irr::scene::ISceneNode *parent)> &factory) :
		EntityGui::ISceneNodeDerivedBase<ISceneNodeType>(factory(getStackScene(), getStackParentNode()))
	{
	}

	~ISceneNodeDerived(void) override
	{
	}
};

}

#include "EntityGuiWorld.hpp"

namespace en = Engine;
