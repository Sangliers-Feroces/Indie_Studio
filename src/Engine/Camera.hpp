#pragma once

#include "Entity.hpp"

namespace Engine {

class Camera : public Entity::ISceneNodeDerived<irr::scene::ICameraSceneNode>
{
public:
	Camera(void);
	~Camera(void);
};

}