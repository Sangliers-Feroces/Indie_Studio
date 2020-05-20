#pragma once

#include "Entity.hpp"

namespace Engine {

class Mesh : public Entity::ISceneNodeDerived<irr::scene::IMeshSceneNode>
{
public:
	Mesh(irr::scene::IMesh &mesh);
	~Mesh(void);
};

}