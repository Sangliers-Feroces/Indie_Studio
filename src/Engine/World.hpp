#pragma once

#include <stack>
#include <chrono>
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

			void setScale(double scale);

		private:
			std::chrono::high_resolution_clock::time_point m_time_before;
			double m_scale;
			friend Events;
			void updateObserver(void);
		} update;

	private:
		friend Session;
		void updateObserver(void);
	} events;

private:
	friend Entity;

	irr::scene::ISceneManager &m_irr_scene;
};

}

#include "Session.hpp"