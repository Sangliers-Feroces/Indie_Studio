#pragma once

#include "Engine/World.hpp"
#include "Engine/Camera.hpp"
#include "Player.hpp"

namespace Bomberman {

class Field : public en::World
{
public:
	Field(void);
	~Field(void);

private:
	en::Camera &m_camera;
	Player &m_player;
};

}