#pragma once

#include "Entity.hpp"

namespace Engine {

class AnimatedMesh : public Entity::ISceneNodeDerived<irr::scene::IAnimatedMeshSceneNode>
{
public:
	AnimatedMesh(irr::scene::IAnimatedMesh &mesh);
	~AnimatedMesh(void);
};

}