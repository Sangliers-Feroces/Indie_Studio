#pragma once

#include "Mob.hpp"

namespace Bomberman {

class Player : public Mob
{
public:
	Player(size_t id);
	~Player(void);

private:
	size_t m_bombs;
	double m_time_before_bomb;

	static double reload_rate;
	static size_t max_bombs;

	class Controller
	{
	public:
		virtual ~Controller(void) = default;

		void scan(void);

		enum class Key {
			Left,
			Right,
			Up,
			Down,
			Fire
		};

		virtual bool getState(Key key) const = 0;
		bool isPressed(Key key);
		bool isReleased(Key key);

	protected:
		virtual void refresh(void) = 0;

		static const std::vector<Key>& getKeys(void);

	private:
		std::map<Key, bool> m_last_state;
		std::map<Key, bool> m_cur_state;
	};

	std::unique_ptr<Controller> m_controller;
	std::unique_ptr<Controller> genController(size_t id);

	class LocalController : public Controller
	{
	public:
		enum class Layout {
			Zqsd,
			Arrows
		};

		LocalController(en::Session &session, Layout layout);
		~LocalController(void) override;

		void refresh(void) override;

		bool getState(Key key) const override;

	private:
		en::Session &m_session;
		Layout m_layout;
		const std::map<Key, irr::EKEY_CODE> &m_key_set;

		const std::map<Key, irr::EKEY_CODE>& getKeySet(Layout layout);
		irr::EKEY_CODE getKeyCode(Key abstract_key) const;
	};

	class BotController : public Controller
	{
	public:
		BotController(Field &field, Player &me);
		~BotController(void) override;

		void refresh(void) override;
		bool getState(Key key) const override;

	private:
		Field &m_field;
		Player &m_me;

		std::map<Key, bool> m_keys;
	};

	friend BotController;
};

}