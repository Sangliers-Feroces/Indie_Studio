#include "Player.hpp"
#include "Bomb.hpp"

#include <iostream>

namespace Bomberman {

Player::Player(size_t id) :
	Mob("res/models/box.obj", "res/models/Steve.png"),
	m_last_key(irr::KEY_ESCAPE),
	m_bombs(1),
	m_time_before_bomb(reload_rate)
{
	int w_max = field.getWidth() - 1;
	int h_max = field.getHeight() - 1;
	const std::map<size_t, irr::core::vector2di> spawns = {
		{0, {0, 0}},
		{1, {w_max, 0}},
		{2, {0, h_max}},
		{3, {w_max, h_max}},
	};

	setPos(irr::core::vector2di(spawns.at(id)));
	setScale(irr::core::vector3df(0.5));

	bind(world.session.events.key.pressed, [this](auto key){
		m_last_key = key;
	});

	static const std::map<irr::EKEY_CODE, irr::core::vector2di> directions = {
		{irr::KEY_UP, irr::core::vector2di(0, 1)},
		{irr::KEY_DOWN, irr::core::vector2di(0, -1)},
		{irr::KEY_LEFT, irr::core::vector2di(-1, 0)},
		{irr::KEY_RIGHT, irr::core::vector2di(1, 0)}
	};

	bind(world.events.update, [&](auto deltaTime) {
		for (auto &p : directions)
			if (world.session.events.key.getState(p.first))
				move(p.second, 5.0);

		m_time_before_bomb -= deltaTime;
		if (m_time_before_bomb <= 0.0) {
			m_bombs++;
			if (m_bombs > 3)
				m_bombs = 3;
			m_time_before_bomb += reload_rate;
		}
	});

	bind(world.session.events.key.pressed, [this](auto key){
		if (key == irr::KEY_RCONTROL) {
			if (m_bombs > 0) {
				field.addMob<Bomb>(getIncomingPos());
				m_bombs--;
			}
		}
	});
}

Player::~Player(void)
{
}

double Player::reload_rate = 3.0;

}