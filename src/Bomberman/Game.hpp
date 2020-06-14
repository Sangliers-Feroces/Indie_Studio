#pragma once

#include "Engine/Session.hpp"
#include "Field.hpp"
#include "Menu.hpp"
#include "Gui.hpp"
#include "Pause.hpp"
#include "IGOptions.hpp"
#include "PreGame.hpp"
#include "WinScreen.hpp"

namespace Bomberman {

class Game : public en::Session
{
public:
	Game(void);
	~Game(void) override;
private:
	void player_reset(void);
	std::string genName(void);
	std::reference_wrapper<en::EntityGuiWorld> m_gui;
	en::World *m_world;
	std::vector<Field::PlayerMeta> m_players;
};

}