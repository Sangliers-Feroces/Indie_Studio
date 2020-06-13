#include "FireUp.hpp"

namespace Bomberman {
namespace PowerUp {

FireUp::FireUp(const irr::core::vector2di &pos) :
	Base(pos, "res/models/fireup.png")
{
}

void FireUp::write(std::ostream &o)
{
	en::util::write(o, en::util::type_id<decltype(*this)>());
	Base::write(o);
}

FireUp::FireUp(std::istream &i) :
	Base(i)
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