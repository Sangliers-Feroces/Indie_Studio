#pragma once

#include "World.hpp"
#include "util.hpp"

namespace Engine {

class Session
{
public:
	Session(void);
	virtual ~Session(void) = 0;

private:
	util::irr_shared<irr::IrrlichtDevice> m_irr_device;
};

}