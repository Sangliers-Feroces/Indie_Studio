#pragma once

#include "Engine/AnimatedMesh.hpp"

namespace Bomberman {

class Player : public en::Entity
{
public:
	Player(void);
	~Player(void);

	en::Event::Generator<> pressedZ;
	en::Event::Generator<std::string> message;
	en::Event::Generator<> do_quit;
};

}