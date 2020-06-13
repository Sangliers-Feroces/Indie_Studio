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

void PassUp::write(std::ostream &o)
{
	en::util::write(o, en::util::type_id<decltype(*this)>());
	Base::write(o);
}

void PassUp::onPlayerCollect(Player &player)
{
	auto &stats = getPlayerStats(player);

	stats.wall_pass = true;
	stats.wall_pass_used = false;
}

}
}