#include "CameraFPS.hpp"

namespace Engine {

CameraFPS::CameraFPS(void) :
	Entity::ISceneNodeDerived<irr::scene::ICameraSceneNode>([](auto &scene, auto parent){
		return scene.addCameraSceneNodeFPS(parent);
	})
{
}

CameraFPS::~CameraFPS(void)
{
}

}