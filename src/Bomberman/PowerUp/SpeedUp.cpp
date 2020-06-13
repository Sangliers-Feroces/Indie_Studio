#include "SpeedUp.hpp"

namespace Bomberman {
namespace PowerUp {

SpeedUp::SpeedUp(const irr::core::vector2di &pos) :
	Base(pos, "res/models/skate.png")
{
}

void SpeedUp::write(std::ostream &o)
{
	en::util::write(o, en::util::type_id<decltype(*this)>());
	Base::write(o);
}

SpeedUp::SpeedUp(std::istream &i) :
	Base(i)
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