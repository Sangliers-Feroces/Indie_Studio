#include "FireUp.hpp"

namespace Bomberman {
namespace PowerUp {

FireUp::FireUp(const irr::core::vector2di &pos) :
	Base(pos, "res/models/fireup.png")
{
}

FireUp::~FireUp(void)
{
}

void FireUp::onPlayerCollect(Player &player)
{
	auto &stats = getPlayerStats(player);

	stats.bomb_radius++;
}

}
}