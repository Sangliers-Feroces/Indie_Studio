#pragma once

#include "Entity.hpp"

namespace Engine {

class Light : public Entity::ISceneNodeDerived<irr::scene::ILightSceneNode>
{
public:
	Light(const irr::video::SColor &color, float radius);
	~Light(void);

	void setType(irr::video::E_LIGHT_TYPE type);
	const irr::video::SLight& getData(void) const;
	void setData(const irr::video::SLight &data);

	void enableCastShadow(bool shadow = true);

	using Entity::getPos;
	using Entity::setPos;
	using Entity::getRot;
	using Entity::setRot;
};

}