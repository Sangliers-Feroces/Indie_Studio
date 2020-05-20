#pragma once

#include "Entity.hpp"

namespace Engine {

class CameraFPS : public Entity::ISceneNodeDerived<irr::scene::ICameraSceneNode>
{
public:
	CameraFPS(void);
	~CameraFPS(void);
};

}