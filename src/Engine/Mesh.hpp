#pragma once

#include "Entity.hpp"

namespace Engine {

class Mesh : public Entity::ISceneNodeDerived<irr::scene::IMeshSceneNode>
{
public:
	Mesh(const std::string &mesh_path);
	~Mesh(void);

private:
	Mesh(irr::scene::IMesh &mesh);
};

}