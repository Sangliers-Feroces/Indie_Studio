#define _USE_MATH_DEFINES
#include "Camera.hpp"

namespace Bomberman {

Camera::Camera(size_t w, size_t h)
{
	auto el = 18.0;
	auto pos = irr::core::vector3df(w / 2.0 - 1.0, el, h / 2.0 - 1.0);
	setPos(pos);
	setFOV(M_PI_4);
	setTarget(pos - irr::core::vector3df(0.0, el, 0.0));
	setUpVector(irr::core::vector3df(0.0, 0.0, 1.0));
	/*bind(world.events.update, [this](double delta){
		m_rot.Z += delta;
		setTarget(m_rot);
	});*/

	setNearValue(0.001);
	setFarValue(10000.0);
	/*bind(world.session.events.key.pressed, [this](auto key){
		if (key == irr::KEY_KEY_Z)
		else if (key == irr::KEY_KEY_D)
			setTarget(irr::core::vector3df(100.0, 100.0, 0.0));
	});*/
}

Camera::~Camera(void)
{
}

}