#include "CameraFPS.hpp"

namespace Engine {


CameraFPS::CameraFPS(void) :
	Entity::ISceneNodeDerived<irr::scene::ICameraSceneNode>([](auto parent){
		return getStackScene().addCameraSceneNodeFPS(parent);
	})
{
}

CameraFPS::~CameraFPS(void)
{
}

}