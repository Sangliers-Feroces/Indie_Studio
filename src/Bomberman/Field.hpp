#pragma once

#include "Engine/World.hpp"

namespace Bomberman {

class Field : public en::World
{
public:
	Field(irr::IrrlichtDevice &device);
	~Field(void);
};

}