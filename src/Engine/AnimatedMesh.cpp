#include "AnimatedMesh.hpp"

namespace Engine {

AnimatedMesh::AnimatedMesh(irr::scene::IAnimatedMesh &mesh) :
	Entity::ISceneNodeDerived<irr::scene::IAnimatedMeshSceneNode>([&mesh](auto &scene, auto parent){
		return scene.addAnimatedMeshSceneNode(&mesh, parent);
	})
{
	m_irr_node_der.setMaterialTexture(0, world.driver.getTexture("res/models/dolphin_f.pcx"));
        m_irr_node_der.setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

AnimatedMesh::AnimatedMesh(const std::string &mesh_path) :
	AnimatedMesh(getStackWorld().getMesh(mesh_path))
{
}

AnimatedMesh::~AnimatedMesh(void)
{
}

}