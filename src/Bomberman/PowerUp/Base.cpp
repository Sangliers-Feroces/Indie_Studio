#include "Base.hpp"

namespace Bomberman {
namespace PowerUp {

Base::Base(const irr::core::vector2di &pos, const std::string &texture_path) :
	Mob("res/models/box.obj", texture_path),
	m_collected(false)
{
	setPos(pos);

	init();
}

void Base::init(void)
{
	setScale(irr::core::vector3df(0.7));

	bind(world.events.update, [this](auto){
		auto t = world.events.update.getTime();
		double rot = t * 50.0;
		setRot(irr::core::vector3df(0.0, rot, 0.0));
		updatePos();
		auto off = sin(t * 2.5) * 0.5 + 0.5;
		auto pos = Entity::getPos() + irr::core::vector3df(0.0, off, 0.0);
		Entity::setPos(pos);
	});
}

void Base::write(std::ostream &o)
{
	Mob::write(o);
	en::util::write(o, m_collected);
}

Base::Base(std::istream &i) :
	Mob(i),
	m_collected(en::util::read<decltype(m_collected)>(i))
{
	init();
}

Base::~Base(void)
{
}

void Base::collect(Player &player)
{
	if (m_collected)
		return;
	onPlayerCollect(player);
	m_collected = true;
	world.session.playSound("res/sounds/collect.ogg", 0.5);
	destroy();
}

Player::Stats& Base::getPlayerStats(Player &player)
{
	return player.getStats();
}

}
}