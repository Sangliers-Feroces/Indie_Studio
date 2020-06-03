#pragma once

#include "Entity.hpp"

namespace Engine {

class Camera : public Entity::ISceneNodeDerived<irr::scene::ICameraSceneNode>
{
public:
	Camera(void);
	~Camera(void);

protected:

	void setAspectRatio(irr::f32 aspect);
	void setFarValue(irr::f32 zf);
	void setFOV(irr::f32 fovy);
	void setNearValue(irr::f32 zn);
	void setRotation(const irr::core::vector3df &rotation);
	

};

}