#include "Base.hpp"

namespace Bomberman {
namespace PowerUp {

Base::Base(const irr::core::vector2di &pos, const std::string &texture_path) :
	Mob("res/models/box.obj", texture_path),
	m_collected(false)
{
	setPos(pos);
	setScale(irr::core::vector3df(0.4));
}

Base::~Base(void)
{
}

void Base::collect(Player &player)
{
	if (m_collected)
		return;
	onPlayerCollect(player);
	m_collected = true;
	destroy();
}

Player::Stats& Base::getPlayerStats(Player &player)
{
	return player.getStats();
}

}
}