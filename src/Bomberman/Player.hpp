#pragma once

#include <iostream>
#include <queue>
#include "Mob.hpp"

namespace Bomberman {

namespace PowerUp {
class Base;
}

class Player : public Mob
{
public:
	Player(bool is_bot, const std::string &name, size_t id, size_t player_id);
	void init(void);
	void write(std::ostream &o) override;
	Player(std::istream &i);
	~Player(void);

	void hitByBomb(void);
	en::Event::Generator<> died;
	bool isDead(void) const;
	const std::string& getName(void) const;

	struct Stats
	{
		Stats(void) :
			speed(5.0),
			max_bombs(3),
			bomb_radius(3),
			wall_pass(false),
			wall_pass_used(false)
		{
		}

		double speed;
		size_t max_bombs;
		size_t bomb_radius;
		bool wall_pass;
		bool wall_pass_used;
	};

private:
	Stats m_stats;
	size_t m_bombs;
	double m_time_before_bomb;
	bool m_dead;
	const std::string m_name;
	bool m_is_bot;
	size_t m_difficulty;
	size_t m_bot_it;
	double m_bot_next_action;
	size_t m_player_id;

	bool canMoveTo(const irr::core::vector2di &pos) const override;
	void onMove(const irr::core::vector2di &newpos) override;
	void onAnim(double ratio) override;
	bool isSafeToGo(const irr::core::vector2di &pos);
	bool botEscape(const irr::core::vector2di &pos);
	void insertEntry(std::map<size_t, irr::core::vector2di> &res, const irr::core::vector2di &dir, size_t depth);
	void fillRange(size_t range[4]);
	void checkDir(const irr::core::vector2di &basedir, const irr::core::vector2di &pos, const irr::core::vector2di &dir, size_t depth, std::map<size_t, irr::core::vector2di> &res, std::vector<irr::core::vector2di> &path);
	irr::core::vector2di nearestPlayerVec(void);
	irr::core::vector2df ivectof(const irr::core::vector2di &vec);
	void botUpdate(double delta);
	bool shouldPutBomb(void);

	static double reload_rate;
	static size_t levelToBotIt(size_t level);

	friend PowerUp::Base;
	Stats& getStats(void);

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
		static const std::vector<Key>& getKeys(void);

		virtual bool getState(Key key) const = 0;
		bool isPressed(Key key);
		bool isReleased(Key key);

	protected:
		virtual void refresh(void) = 0;

	private:
		std::map<Key, bool> m_last_state;
		std::map<Key, bool> m_cur_state;
	};

	std::unique_ptr<Controller> m_controller;
	std::queue<Controller::Key> m_next_bot_moves;
	std::unique_ptr<Controller> genController(bool is_bot, size_t player_id);
	static Controller::Key dirToKey(const irr::core::vector2di &dir);

	class LocalController : public Controller
	{
	public:
		LocalController(en::Session &session, size_t layout);
		~LocalController(void) override;

		void refresh(void) override;

		bool getState(Key key) const override;

	private:
		en::Session &m_session;
		size_t m_layout;
		const std::map<Key, irr::EKEY_CODE> &m_key_set;

		const std::map<Key, irr::EKEY_CODE>& getKeySet(size_t layout);
		irr::EKEY_CODE getKeyCode(Key abstract_key) const;
		static std::map<size_t, std::map<Key, irr::EKEY_CODE>> loadBindings(void);
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