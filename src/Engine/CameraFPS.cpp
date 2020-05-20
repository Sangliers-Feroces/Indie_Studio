#include "CameraFPS.hpp"

namespace Engine {

CameraFPSBase::CameraFPSBase(irr::scene::ICameraSceneNode *camera) :
	Entity(camera),
	m_camera(*camera)
{
}

CameraFPSBase::~CameraFPSBase(void)
{
}

CameraFPS::CameraFPS(void) :
	CameraFPSBase(getStackScene().addCameraSceneNodeFPS(getStackParentNode()))
{
}

CameraFPS::~CameraFPS(void)
{
}

}