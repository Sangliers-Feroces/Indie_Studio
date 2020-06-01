#include "Camera.hpp"

namespace Engine {

Camera::Camera(void) :
	Entity::ISceneNodeDerived<irr::scene::ICameraSceneNode>([](auto &scene, auto parent){
		return scene.addCameraSceneNodeFPS(parent);
	})
{
}

Camera::~Camera(void)
{
}

}