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
	EntityGui(const Context &ctx, irr::gui::IGUIEnvironment &env);

protected:
	EntityGui(irr::gui::IGUIElement *irrelem);
	static EntityGuiWorld& getStackWorld(void);
	static irr::gui::IGUIEnvironment& getStackScene(void);
	static irr::gui::IGUIElement* getStackParentElem(void);

public:
	virtual ~EntityGui(void) = 0;

	template <class IGUIElementType>
	class IGUIElementDerivedBase;
	template <class IGUIElementType>
	class IGUIElementDerived;

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

private:
	static std::stack<Context>& getStack(void);
	EntityGui *m_parent;
	util::irr_shared<irr::gui::IGUIElement, true> m_irr_elem;
	util::unique_set<EntityGui> m_children;
};

template <class IGUIElementType>
class EntityGui::IGUIElementDerivedBase : public EntityGui
{
public:
	IGUIElementDerivedBase(IGUIElementType *node) :
		EntityGui(node),
		m_irr_elem_der(util::ptr_to_ref(node))
	{
	}

	~IGUIElementDerivedBase(void) override
	{
	}

protected:
	IGUIElementType &m_irr_elem_der;
};

template <class IGUIElementType>
class EntityGui::IGUIElementDerived : public EntityGui::IGUIElementDerivedBase<IGUIElementType>
{
public:
	IGUIElementDerived(const std::function<IGUIElementType* (irr::gui::IGUIEnvironment &env, irr::gui::IGUIElement *parent)> &factory) :
		EntityGui::IGUIElementDerivedBase<IGUIElementType>(factory(getStackScene(), getStackParentElem()))
	{
	}

	~IGUIElementDerived(void) override
	{
	}
};

}

#include "EntityGuiWorld.hpp"

namespace en = Engine;
