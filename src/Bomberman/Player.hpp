#pragma once

#include "Engine/AnimatedMesh.hpp"
#include "Engine/Mesh.hpp"

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
			en::AnimatedMesh("res/models/minecraft-steve.obj")
		{
			setPos(irr::core::vector3df(x, y, z));
			setScale(irr::core::vector3df(20));
			setMaterialTexture(0, world.driver.getTexture("res/models/Steve.png"));
			setMaterialFlag(irr::video::EMF_LIGHTING, false);
		}
		~Sub(void) = default;
	};
};

}