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

	class Events
	{
	public:
		Events(void);
		~Events(void);

		class Update : public Event::CopyDispatcher<double>
		{
		public:
			Update(void);
			~Update(void);

		private:
			std::chrono::high_resolution_clock::time_point m_time_before;

			friend Events;
			void updateObserver(void);
		} update;

	private:
		friend Session;
		void updateObserver(void);
	} events;

private:
	friend EntityGui;
	irr::gui::IGUIEnvironment &m_env;
};

}

#include "Session.hpp"