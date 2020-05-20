#pragma once

#include "Engine/AnimatedMesh.hpp"

namespace Bomberman {

class Player : public en::AnimatedMesh
{
public:
	Player(void);
	~Player(void);
};

}