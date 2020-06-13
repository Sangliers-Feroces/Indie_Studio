#pragma once

#include "Base.hpp"

namespace Bomberman {
namespace PowerUp {

class BombUp : public Base
{
public:
	BombUp(const irr::core::vector2di &pos);
	void write(std::ostream &o) override;
	BombUp(std::istream &i);
	~BombUp(void) override;

	void onPlayerCollect(Player &player) override;
};

}
}