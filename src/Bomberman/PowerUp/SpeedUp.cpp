#include "SpeedUp.hpp"

namespace Bomberman {
namespace PowerUp {

SpeedUp::SpeedUp(const irr::core::vector2di &pos) :
	Base(pos, "res/models/skate.png")
{
}

SpeedUp::~SpeedUp(void)
{
}

void SpeedUp::onPlayerCollect(Player &player)
{
	auto &stats = getPlayerStats(player);

	stats.speed++;
}

}
}