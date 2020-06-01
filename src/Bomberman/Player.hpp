#pragma once

#include "Engine/AnimatedMesh.hpp"
#include "Engine/Mesh.hpp"
#include "util/crossplatform.hpp"

#if defined(_PLATFORM_WINDOWS)
	#include <BaseTsd.h>

	typedef SSIZE_T ssize_t;
#elif defined(_PLATFORM_POSIX)
#else
#error Unsupported platform
#endif


namespace Bomberman {

class Player : public en::Entity
{
public:
	Player(void);
	~Player(void);

	class Sub : public en::AnimatedMesh
	{
	public:
		Sub(ssize_t x, ssize_t y, ssize_t z) :
			en::AnimatedMesh("res/models/minecraft-steve.obj")
		{
			setPos(irr::core::vector3df(x, y, z));
			setScale(irr::core::vector3df(20));
			setMaterialTexture(0, world.driver.getTexture("res/models/Steve.png"));
			setMaterialFlag(irr::video::EMF_LIGHTING, false);
		}

		template <typename ...Args>
		void setTexture(Args&&...args)
		{
			auto tex = world.driver.getTexture(std::forward<Args>(args)...);
			setMaterialTexture(0, tex);
		}

		~Sub(void) = default;
	};
};

}