#pragma once

#include "Engine/Entity.hpp"

namespace Bomberman {

class Player : public en::Entity
{
public:
	Player(const en::Entity::Context &ctx);
	~Player(void);
};

}