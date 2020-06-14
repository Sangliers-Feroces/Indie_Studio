#include "Light.hpp"

namespace Engine {

Light::Light(const irr::video::SColor &color, float radius) :
	Entity::ISceneNodeDerived<irr::scene::ILightSceneNode>([&](auto &scene, auto parent){
		return scene.addLightSceneNode(parent, irr::core::vector3df(0, 0, 0), color, radius);
	})
{
}

Light::~Light(void)
{
}

void Light::enableCastShadow(bool shadow)
{
	m_irr_node_der.enableCastShadow(shadow);
}

void Light::setType(irr::video::E_LIGHT_TYPE type)
{
	m_irr_node_der.setLightType(type);
}

const irr::video::SLight& Light::getData(void) const
{
	return m_irr_node_der.getLightData();
}

void Light::setData(const irr::video::SLight &data)
{
	m_irr_node_der.setLightData(data);
}

}