#pragma once

#include "Engine/AnimatedMesh.hpp"

namespace Bomberman {

class Player : public en::Entity
{
public:
	Player(void);
	~Player(void);

	class Sub : public en::AnimatedMesh
	{
	public:
		Sub(int64_t x, int64_t y, int64_t z) :
			en::AnimatedMesh("res/models/dolphin.md2")
		{
			setPos(irr::core::vector3df(x, y, z));
		}
		~Sub(void) = default;
	};
};

}