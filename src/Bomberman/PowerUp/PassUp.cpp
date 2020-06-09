#include "PassUp.hpp"

namespace Bomberman {
namespace PowerUp {

PassUp::PassUp(const irr::core::vector2di &pos) :
	Base(pos, "res/models/blockpass.png")
{
}

PassUp::~PassUp(void)
{
}

void PassUp::onPlayerCollect(Player &player)
{
	auto &stats = getPlayerStats(player);

	stats.wall_pass = true;
}

}
}