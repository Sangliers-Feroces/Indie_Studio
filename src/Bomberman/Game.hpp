#pragma once

#include "Engine/Session.hpp"
#include "Field.hpp"
#include "Gui.hpp"

namespace Bomberman {

class Game : public en::Session
{
public:
	Game(void);
	~Game(void) override;

protected:
	bool isDone(void) const override;

private:
	Field &m_field;
	Gui &m_gui;
	bool m_stop_run;
};

}