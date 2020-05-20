#pragma once

#include "Entity.hpp"

namespace Engine {

class AnimatedMesh : public Entity::ISceneNodeDerived<irr::scene::IAnimatedMeshSceneNode>
{
public:
	AnimatedMesh(const std::string &mesh_path);
	~AnimatedMesh(void);

private:
	AnimatedMesh(irr::scene::IAnimatedMesh &mesh);
};

}