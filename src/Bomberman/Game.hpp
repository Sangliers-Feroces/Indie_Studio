#pragma once

#include "Engine/Session.hpp"
#include "Field.hpp"

namespace Bomberman {

class Game : public en::Session
{
public:
	Game(void);
	~Game(void) override;

private:
	Field &m_field;
};

}