#pragma once

#include "Entity.hpp"

namespace Engine {

class CameraFPSBase : public Entity
{
public:
	CameraFPSBase(irr::scene::ICameraSceneNode *camera);
	~CameraFPSBase(void);

private:
	irr::scene::ICameraSceneNode &m_camera;
};

class CameraFPS : public CameraFPSBase
{
public:
	CameraFPS(void);
	~CameraFPS(void);
};

}