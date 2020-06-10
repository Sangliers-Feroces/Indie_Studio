/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityGuiWorld
*/

#pragma once

#include <stack>
#include <chrono>
#include "EntityGui.hpp"

namespace Engine {

class Session;

class EntityGuiWorld : public EntityGui
{
public:
	EntityGuiWorld(void);
	virtual ~EntityGuiWorld(void) override = 0;
private:
	friend Session;
	static std::stack<std::reference_wrapper<Session>>& getStack(void);

public:
	Session &session;

private:
	friend EntityGui;
	irr::gui::IGUIEnvironment &m_env;
};

}

#include "Session.hpp"