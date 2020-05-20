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
		Sub(ssize_t x, ssize_t y, ssize_t z) :
			en::AnimatedMesh("res/models/dolphin.md2")
		{
			setPos(irr::core::vector3df(x, y, z));
		}
		~Sub(void) = default;
	};
};

}