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
	static std::stack<std::reference_wrapper<Session>>& getStack(void);

public:
	Session &session;

private:
	friend Entity;

	irr::scene::ISceneManager &m_irr_scene;
};

}

#include "Session.hpp"