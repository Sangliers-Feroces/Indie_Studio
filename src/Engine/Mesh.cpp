#include "Mesh.hpp"

namespace Engine {

Mesh::Mesh(irr::scene::IMesh &mesh) :
	Entity::ISceneNodeDerived<irr::scene::IMeshSceneNode>([&mesh](auto parent){
		return getStackScene().addMeshSceneNode(&mesh, parent);
	})
{
}

Mesh::Mesh(const std::string &mesh_path) :
	Mesh(getStackWorld().getMesh(mesh_path))
{
}

Mesh::~Mesh(void)
{
}

}