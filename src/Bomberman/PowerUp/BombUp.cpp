#include "BombUp.hpp"

namespace Bomberman {
namespace PowerUp {

BombUp::BombUp(const irr::core::vector2di &pos) :
	Base(pos, "res/models/bombup.png")
{
}

void BombUp::write(std::ostream &o)
{
	en::util::write(o, en::util::type_id<decltype(*this)>());
	Base::write(o);
}

BombUp::BombUp(std::istream &i) :
	Base(i)
{
}

BombUp::~BombUp(void)
{
}

void BombUp::onPlayerCollect(Player &player)
{
	auto &stats = getPlayerStats(player);

	stats.max_bombs++;
}

}
}