#pragma once

#include "Base.hpp"

namespace Bomberman {
namespace PowerUp {

class SpeedUp : public Base
{
public:
	SpeedUp(const irr::core::vector2di &pos);
	void write(std::ostream &o) override;
	SpeedUp(std::istream &i);
	~SpeedUp(void) override;

	void onPlayerCollect(Player &player) override;
};

}
}