#pragma once

#include "Engine/Camera.hpp"

namespace Bomberman {

class Camera : public en::Camera
{
public:
	Camera(size_t w, size_t h);
	~Camera(void);

private:
	irr::core::vector3df m_rot;
};

}