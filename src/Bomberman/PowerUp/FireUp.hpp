#pragma once

#include "Base.hpp"

namespace Bomberman {
namespace PowerUp {

class FireUp : public Base
{
public:
	FireUp(const irr::core::vector2di &pos);
	void write(std::ostream &o) override;
	FireUp(std::istream &i);
	~FireUp(void) override;

	void onPlayerCollect(Player &player) override;
};

}
}