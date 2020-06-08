#include "Camera.hpp"

namespace Engine {

Camera::Camera(void) :
	Entity::ISceneNodeDerived<irr::scene::ICameraSceneNode>([](auto &scene, auto parent){
		return scene.addCameraSceneNode(parent);
	})
{
}

Camera::~Camera(void)
{
}

irr::f32 Camera::getAspectRatio(void) const
{
	return m_irr_node_der.getAspectRatio();
}

irr::f32 Camera::getFarValue(void) const
{
	return m_irr_node_der.getFarValue();
}

irr::f32 Camera::getFOV(void) const
{
	return m_irr_node_der.getFOV();
}

irr::f32 Camera::getNearValue(void) const
{
	return m_irr_node_der.getNearValue();
}

const irr::core::vector3df& Camera::getTarget() const
{
	return m_irr_node_der.getTarget();
}

void Camera::setAspectRatio(irr::f32 aspect)
{
	m_irr_node_der.setAspectRatio(aspect);
}

void Camera::setFarValue(irr::f32 zf)
{
	m_irr_node_der.setFarValue(zf);
}

void Camera::setFOV(irr::f32 fovy)
{
	m_irr_node_der.setFOV(fovy);
}

void Camera::setNearValue(irr::f32 zn)
{
	m_irr_node_der.setNearValue(zn);
}

void Camera::setRotation(const irr::core::vector3df &rotation)
{
	m_irr_node_der.setRotation(rotation);
}

void Camera::setTarget(const irr::core::vector3df &pos)
{
	m_irr_node_der.setTarget(pos);
}

void Camera::setUpVector(const irr::core::vector3df &up)
{
	m_irr_node_der.setUpVector(up);
}

}