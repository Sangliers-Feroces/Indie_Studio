#pragma once

#include "../Player.hpp"

namespace Bomberman {
namespace PowerUp {

class Base : public Mob
{
public:
	Base(const irr::core::vector2di &pos, const std::string &texture_path);
	void write(std::ostream &o) override;
	virtual ~Base(void) = 0;

	void collect(Player &player);

protected:
	bool m_collected;

	virtual void onPlayerCollect(Player &player) = 0;
	Player::Stats& getPlayerStats(Player &player);
};

}
}