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

void SpeedUp::write(std::ostream &o)
{
	en::util::write(o, en::util::type_id<decltype(*this)>());
	Base::write(o);
}

void SpeedUp::onPlayerCollect(Player &player)
{
	auto &stats = getPlayerStats(player);

	stats.speed++;
}

}
}