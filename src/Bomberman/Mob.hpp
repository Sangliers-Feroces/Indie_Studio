#pragma once

#include "Model.hpp"

namespace Bomberman {

class Field;

class Mob : public Model
{
public:
	Mob(const std::string &model_path, const std::string &texture_path);
	~Mob(void);

protected:
	Field &field;

	bool move(const irr::core::vector2di &dir, double speed);
	const irr::core::vector2di& getPos(void) const;
	void setPos(const irr::core::vector2di &newpos);

private:
	irr::core::vector2di m_pos;
	irr::core::vector2di m_dir;
	double m_speed;
	double m_move_ratio;

	void updatePos(void);
	bool canMoveTo(const irr::core::vector2di &pos) const;

	friend Field;
	static std::stack<std::reference_wrapper<Field>>& getStack(void);
};

}

#include "Field.hpp"
