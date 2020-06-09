#include "BombUp.hpp"

namespace Bomberman {
namespace PowerUp {

BombUp::BombUp(const irr::core::vector2di &pos) :
	Base(pos, "res/models/bombup.png")
{
}

BombUp::~BombUp(void)
{
}

void BombUp::onPlayerCollect(Player &player)
{
	auto &stats = getPlayerStats(player);

	stats.bomb_radius++;
}

}
}