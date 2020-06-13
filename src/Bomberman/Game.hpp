#pragma once

#include "Engine/Session.hpp"
#include "Field.hpp"
#include "Menu.hpp"
#include "Gui.hpp"
#include "Pause.hpp"
#include "IGOptions.hpp"
#include "PreGame.hpp"

namespace Bomberman {

class Game : public en::Session
{
public:
	Game(void);
	~Game(void) override;

protected:
	bool isDone(void) const override;

private:
	std::reference_wrapper<en::EntityGuiWorld> m_gui;
	en::World *m_world;
	bool m_stop_run;
};

}