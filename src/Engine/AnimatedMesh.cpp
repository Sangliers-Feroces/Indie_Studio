#include "AnimatedMesh.hpp"

namespace Engine {

AnimatedMesh::AnimatedMesh(irr::scene::IAnimatedMesh &mesh) :
	Entity::ISceneNodeDerived<irr::scene::IAnimatedMeshSceneNode>([&mesh](auto &scene, auto parent){
		return scene.addAnimatedMeshSceneNode(&mesh, parent);
	})
{
}

AnimatedMesh::AnimatedMesh(const std::string &mesh_path) :
	AnimatedMesh(getStackWorld().session.getMesh(mesh_path))
{
}

AnimatedMesh::~AnimatedMesh(void)
{
}

}