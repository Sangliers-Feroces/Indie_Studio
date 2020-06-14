#pragma once

#include <iostream>
#include "Model.hpp"

namespace Bomberman {

class Field;

class Mob : public Model
{
public:
	Mob(const std::string &model_path, const std::string &texture_path);
	void init(void);
	virtual void write(std::ostream &o);
	Mob(std::istream &i);
	virtual ~Mob(void) = 0;

protected:
	Field &field;

	bool move(const irr::core::vector2di &dir, double speed);
	const irr::core::vector2di& getPos(void) const;
	irr::core::vector2di getIncomingPos(void) const;
	void setPos(const irr::core::vector2di &newpos);
	virtual void onMove(const irr::core::vector2di &newpos);
	bool isMoving(void);

private:
	irr::core::vector2di m_pos;
	irr::core::vector2di m_dir;
	double m_speed;
	double m_move_ratio;
	double m_angle_start;
	double m_angle_end;

	void updatePos(void);
	virtual bool canMoveTo(const irr::core::vector2di &pos) const;

	friend Field;
	static std::stack<std::reference_wrapper<Field>>& getStack(void);
};

}

#include "Field.hpp"
