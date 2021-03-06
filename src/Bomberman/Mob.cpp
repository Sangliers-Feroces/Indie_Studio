#include "Mob.hpp"

namespace Bomberman {

Mob::Mob(const std::string &model_path, const std::string &texture_path) :
	Model(model_path, texture_path),
	field(getStack().top()),
	m_pos(0),
	m_dir(0),
	m_speed(0.0),
	m_move_ratio(1.0),
	m_angle_start(0.0)
{
	field.at(getPos()).addMob(*this);
	init();
}

void Mob::init(void)
{
	bind(world.events.update, [this](auto delta){
		if (m_move_ratio == 1.0) {
			//onIntersection(getOptions());
		} else {
			m_move_ratio += m_speed * delta;
			auto pos = m_pos;
			if (m_move_ratio > 1.0) {
				m_move_ratio = 1.0;
				setPos(m_pos + m_dir);
			}
			auto np = irr::core::vector2df(pos.X, pos.Y) + irr::core::vector2df(m_dir.X, m_dir.Y) * m_move_ratio;
			Entity::setPos(irr::core::vector3df(np.X, 0.0, np.Y));
			onAnim(m_move_ratio);
		}
	});
}

void Mob::write(std::ostream &o)
{
	Model::write(o);
	en::util::write(o, m_pos);
	en::util::write(o, m_dir);
	en::util::write(o, m_speed);
	en::util::write(o, m_move_ratio);
}

Mob::Mob(std::istream &i) :
	Model(i),
	field(getStack().top()),
	m_pos(en::util::read<decltype(m_pos)>(i)),
	m_dir(en::util::read<decltype(m_dir)>(i)),
	m_speed(en::util::read<decltype(m_speed)>(i)),
	m_move_ratio(en::util::read<decltype(m_move_ratio)>(i))
{
	init();
	updatePos();
}

Mob::~Mob(void)
{
	field.at(getPos()).removeMob(*this);
}

double Mob::getAngleStart(void) const
{
	return m_angle_start;
}

double Mob::getAngleEnd(void) const
{
	return m_angle_end;
}

bool Mob::move(const irr::core::vector2di &dir, double speed)
{
	if (m_move_ratio == 1.0 && (std::abs(dir.X) + std::abs(dir.Y)) > 0 && canMoveTo(m_pos + dir)) {
		m_dir = dir;
		m_speed = speed;
		m_move_ratio = 0.0;
		m_angle_start = m_angle_end;
		m_angle_end = dir.getAngle() + 90.0;
		//setRot(-dvec2(dir).angle());
		return true;
	}
	return false;
}

bool Mob::canMoveTo(const irr::core::vector2di &pos) const
{
	return field.typeAt(pos) == Tile::Type::Air;
}

const irr::core::vector2di& Mob::getPos(void) const
{
	return m_pos;
}

irr::core::vector2di Mob::getIncomingPos(void) const
{
	if (m_move_ratio == 1.0)
		return m_pos;
	else
		return m_pos + m_dir;
}

void Mob::setPos(const irr::core::vector2di &newpos)
{
	field.at(getPos()).removeMob(*this);
	m_pos = newpos;
	updatePos();
	field.at(getPos()).addMob(*this);
	onMove(newpos);
}

void Mob::onMove(const irr::core::vector2di&)
{
}

void Mob::onAnim(double)
{
}

bool Mob::isMoving(void)
{
	return m_move_ratio < 1.0;
}

void Mob::updatePos(void)
{
	auto pos = irr::core::vector3df(m_pos.X, 0.0, m_pos.Y);
	Entity::setPos(pos);
}

std::stack<std::reference_wrapper<Field>>& Mob::getStack(void)
{
	static std::stack<std::reference_wrapper<Field>> res;

	return res;
}

}