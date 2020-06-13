#pragma once

#include "Base.hpp"

namespace Bomberman {
namespace PowerUp {

class PassUp : public Base
{
public:
	PassUp(const irr::core::vector2di &pos);
	void write(std::ostream &o) override;
	~PassUp(void) override;

	void onPlayerCollect(Player &player) override;
};

}
}