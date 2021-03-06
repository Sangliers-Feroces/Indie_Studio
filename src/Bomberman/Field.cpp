#include "Field.hpp"
#include "PowerUp/PassUp.hpp"
#include "PowerUp/SpeedUp.hpp"
#include "PowerUp/FireUp.hpp"
#include "PowerUp/BombUp.hpp"
#include "Bomb.hpp"
#include "Sparks.hpp"
#include "Engine/Light.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Bomberman {

Field::Field(const std::vector<PlayerMeta> &players, Env env) :
	m_env(env),
	m_tiles(genTiles()),
	m_w(m_tiles.at(0).size()),
	m_h(m_tiles.size()),
	m_camera(add<Camera>(m_w, m_h)),
	m_wall(add<Tile>(Tile::Type::Wall, irr::core::vector2di(-1000, -1000), *this)),
	m_players_alive(0)
{
	size_t id = 0;
	size_t player_id = 0;
	for (auto &m : players) {
		auto &p = addMob<Player>(m.is_bot, m.name.size() == 0 ? id_to_str(id) : m.name, id, player_id);
		bindPlayer(p);
		m_players_alive++;
		if (!m.is_bot)
			player_id++;
		id++;
	}
	init();
}

void Field::init(void)
{
	addBarrier();
	for (size_t i = 0; i < 2; i++) {
		auto &l = add<en::Light>(irr::video::SColor(0xFFFFFFFF), 500.0);
		l.enableCastShadow();
		l.setType(irr::video::E_LIGHT_TYPE::ELT_DIRECTIONAL);
		l.setRot(irr::core::vector3df(90.0 + 45.0, 0.0, -20.0));
		auto d = l.getData();
		d.AmbientColor = irr::video::SColor(0xFFAAAAFF);
		d.SpecularColor = irr::video::SColor(0);
		l.setData(d);
	}

	/*auto &amb = add<en::Light>(irr::video::SColor(0x80AAAAFF), 500.0);
	amb.setType(irr::video::E_LIGHT_TYPE::ELT_DIRECTIONAL);
	amb.setRot(irr::core::vector3df(90.0, 0.0, 0.0));*/

	bind(world.session.events.key.pressed, [&](auto key){
		if (key == irr::KEY_ESCAPE)
			session.switch_Pause = true;
	});
	addAnim();
	playMusic();
}

void Field::bindPlayer(Player &p)
{
	m_players.emplace_back(p);
		bind(p.died, [&](){
			m_players_alive--;
			if (m_players_alive == 1) {
				for (auto &p : m_players)
					if (!p.get().isDead()) {
						session.stop_run(p.get().getName());
					}
			}
	});
}

void Field::write(std::ostream &o)
{
	en::util::write(o, m_env);
	en::util::write(o, m_w);
	en::util::write(o, m_h);
	for (auto &r : m_tiles)
		for (auto &t : r)
			t.get().write(o);
	m_wall.write(o);
	en::util::write(o, m_players_alive);
}

std::vector<std::vector<std::reference_wrapper<Tile>>> Field::readTiles(std::istream &i)
{
	std::vector<std::vector<std::reference_wrapper<Tile>>> res;
	auto w = en::util::read<size_t>(i);
	auto h = en::util::read<size_t>(i);

	for (size_t it = 0; it < h; it++) {
		std::vector<std::reference_wrapper<Tile>> row;
		for (size_t j = 0; j < w; j++)
			row.emplace_back(add<Tile>(i, *this));
		res.emplace_back(std::move(row));
	}
	return res;
}

Field::Field(std::istream &i) :
	m_env(en::util::read<decltype(m_env)>(i)),
	m_tiles(readTiles(i)),
	m_w(m_tiles.at(0).size()),
	m_h(m_tiles.size()),
	m_camera(add<Camera>(m_w, m_h)),
	m_wall(add<Tile>(i, *this)),
	m_players_alive(en::util::read<decltype(m_players_alive)>(i))
{
	for (auto &r : m_tiles)
		for (auto &t : r)
			for (auto &m : t.get().getMobs()) {
				auto &mob = m.get();
				try {
					auto &player = dynamic_cast<Player&>(mob);
					bindPlayer(player);
				} catch (const std::bad_cast&) {}
			}
	init();
}

Field::~Field(void)
{
	for (auto &e : getChildren()) {
		try {
			auto &mob = dynamic_cast<Mob&>(e);
			mob.destroy();
		} catch (const std::bad_cast&) {}
	}
	collectGarbage();
}

const std::vector<Field::Env>& Field::getEnvs(void)
{
	static const std::vector<Env> res = {
		Env::Overworld,
		Env::Mario,
		Env::Beach,
		Env::Doom,
		Env::Sky,
		Env::Volcano
	};

	return res;
}

Tile& Field::at(const irr::core::vector2di &pos)
{
	if (pos.Y >= 0 && pos.Y < (int)m_tiles.size()) {
		auto &row = m_tiles.at(pos.Y);
		if (pos.X >= 0 && pos.X < (int)row.size())
			return row.at(pos.X);
	}
	return m_wall;
}

Tile::Type Field::typeAt(const irr::core::vector2di &pos)
{
	return at(pos).getType();
}

void Field::nuke(const irr::core::vector2di &pos, bool is_simulation)
{
	if (is_simulation) {
		m_bombs.at(pos.Y).at(pos.X) = true;
	} else {
		if (typeAt(pos) == Tile::Type::Box) {
			genItem(pos);
			session.playSoundRnd("res/sounds/box", 4, 0.3);
		}
		at(pos).setType(Tile::Type::Air);
	}
}

void Field::genItem(const irr::core::vector2di &pos)
{
	static const std::vector<std::pair<size_t, const std::function<bool (Field &f, const irr::core::vector2di&)>>> items = {
		{1, [](auto &f, auto &pos){
			f.template addMob<PowerUp::PassUp>(pos);
			return true;
		}},
		{2, [](auto &f, auto &pos){
			f.template addMob<PowerUp::SpeedUp>(pos);
			return true;
		}},
		{2, [](auto &f, auto &pos){
			f.template addMob<PowerUp::FireUp>(pos);
			return true;
		}},
		{3, [](auto &f, auto &pos){
			f.template addMob<PowerUp::BombUp>(pos);
			return true;
		}},
		{8, [](auto&, auto&){
			return false;
		}}
	};
	size_t sum = 0;

	for (auto &p : items)
		sum += p.first;

	size_t got = world.session.randInt(sum);

	size_t goti = 0;
	for (auto &p : items) {
		if (goti >= got) {
			p.second(*this, pos);
			return;
		}
		goti += p.first;
	}
}

Field::Env Field::getEnv(void) const
{
	return m_env;
}

size_t Field::getWidth(void) const
{
	return m_w;
}

size_t Field::getHeight(void) const
{
	return m_h;
}

void Field::updateBombMap(void)
{
	m_bombs.clear();

	for (size_t i = 0; i < m_h; i++) {
		std::vector<bool> row;
		for (size_t j = 0; j < m_w; j++)
			row.emplace_back(false);
		m_bombs.emplace_back(std::move(row));
	}
	for (auto &r : m_tiles)
		for (auto &t : r)
			for (auto &m : t.get().getMobs()) {
				auto &mob = m.get();
				try {
					dynamic_cast<Bomb&>(mob).nuke(true);
				} catch (const std::bad_cast&) {}
				try {
					dynamic_cast<Sparks&>(mob).simulate();
				} catch (const std::bad_cast&) {}
			}
}

bool Field::isBombed(const irr::core::vector2di &pos)
{
	if (pos.Y >= 0 && pos.Y < (int64_t)m_h && pos.X >= 0 && pos.X < (int64_t)m_w)
		return m_bombs.at(pos.Y).at(pos.X);
	else
		return false;
}

bool Field::anySpark(const irr::core::vector2di &pos)
{
	for (auto &m : at(pos).getMobs()) {
		try {
			auto &s = dynamic_cast<Sparks&>(m.get());
			if (s.stillDeadly())
				return true;
		} catch (const std::bad_cast&) {}
	}
	return false;
}

std::vector<std::reference_wrapper<Player>> Field::getPlayers(void)
{
	return m_players;
}

std::string Field::id_to_str(size_t id)
{
	std::stringstream ss;

	ss << (id + 1);
	return ss.str();
}

std::vector<std::vector<Tile::Type>> Field::genField(void)
{
	std::vector<std::vector<Tile::Type>> res;
	size_t h = 10;
	size_t w = 14;
	int wi = w;
	int hi = h;
	std::vector<irr::core::vector2di> air = {
		{0, 0},
		{1, 0},
		{0, 1},

		{wi - 1, hi - 1},
		{wi - 2, hi - 1},
		{wi - 1, hi - 2},

		{wi - 1, 0},
		{wi - 2, 0},
		{wi - 1, 1},

		{0, hi - 1},
		{1, hi - 1},
		{0, hi - 2},
	};

	for (size_t i = 0; i < h; i++) {
		std::vector<Tile::Type> row;
		for (size_t j = 0; j < w; j++) {
			auto p = irr::core::vector2di(j, i);
			auto type = Tile::Type::Air;
			bool isAir = false;
			size_t random_number = world.session.randInt(6);
			for (auto &a : air)
				if (a == p)
					isAir = true;
			if (!isAir) {
				if (random_number == 0)
					type = Tile::Type::Wall;
				else if (random_number == 1)
					type = Tile::Type::Air;
				else
					type = Tile::Type::Box;
			}
			row.emplace_back(type);
		}
		res.emplace_back(row);
	}
	return res;
}

const std::string& Field::typeToTexture(Tile::Type type)
{
	static const std::map<Env, std::map<Tile::Type, std::string>> table = {
		{Env::Overworld, {
			{Tile::Type::Box, "res/env/ow/box.jpg"},
			{Tile::Type::Wall, "res/env/ow/wall.jpg"},
			{Tile::Type::Air, "res/env/ow/box.jpg"},
			{Tile::Type::Ground, "res/env/ow/grass.jpg"}
		}}, {Env::Mario, {
			{Tile::Type::Box, "res/env/mario/box.jpg"},
			{Tile::Type::Wall, "res/env/mario/wall.jpg"},
			{Tile::Type::Air, "res/env/mario/box.jpg"},
			{Tile::Type::Ground, "res/env/ow/grass.jpg"}
		}},
		{Env::Beach, {
			{Tile::Type::Box, "res/env/beach/box.jpg"},
			{Tile::Type::Wall, "res/env/beach/wall.jpg"},
			{Tile::Type::Air, "res/env/beach/box.jpg"},
			{Tile::Type::Ground, "res/env/beach/ground.jpg"}
		}},
		{Env::Doom, {
			{Tile::Type::Box, "res/env/doom/box.jpg"},
			{Tile::Type::Wall, "res/env/doom/wall.jpg"},
			{Tile::Type::Air, "res/env/doom/box.jpg"},
			{Tile::Type::Ground, "res/env/doom/ground.jpg"}
		}},
		{Env::Sky, {
			{Tile::Type::Box, "res/env/sky/box.jpg"},
			{Tile::Type::Wall, "res/env/sky/wall.png"},
			{Tile::Type::Air, "res/env/sky/box.jpg"},
			{Tile::Type::Ground, "res/env/sky/ground.jpg"}
		}},
		{Env::Volcano, {
			{Tile::Type::Box, "res/env/volcano/box.png"},
			{Tile::Type::Wall, "res/env/volcano/wall.png"},
			{Tile::Type::Air, "res/env/volcano/box.png"},
			{Tile::Type::Ground, "res/env/volcano/ground.png"}
		}}
	};

	return table.at(m_env).at(type);
}

std::vector<std::vector<std::reference_wrapper<Tile>>> Field::genTiles(void)
{
	std::vector<std::vector<std::reference_wrapper<Tile>>> res;

	auto field = genField();
	for (size_t i = 0; i < field.size(); i++) {
		auto &field_row = field.at(i);
		std::vector<std::reference_wrapper<Tile>> row;
		for (size_t j = 0; j < field_row.size(); j++)
			row.emplace_back(add<Tile>(field_row.at(j), irr::core::vector2di(j, i), *this));
		res.emplace_back(row);
	}
	return res;
}

void Field::addBarrier(void)
{
	int64_t radius = 1;
	for (int64_t i = -radius; i < ((int64_t)m_h + radius); i++)
		for (int64_t j = -radius; j < ((int64_t)m_w + radius); j++) {
			if (!((i >= 0 && i < (int64_t)m_h) && (j >= 0 && j < (int64_t)m_w)))
				add<Tile>(Tile::Type::Wall, irr::core::vector2di(j, i), *this);
		}
	
	radius = 7;
	for (int64_t i = -radius; i < ((int64_t)m_h + radius); i++)
		for (int64_t j = -radius; j < ((int64_t)m_w + radius); j++) {
			add<Tile>(Tile::Type::Ground, irr::core::vector2di(j, i), *this, -1);
		}
}

void Field::addAnim(void)
{
	const std::map<Env, std::function<std::unique_ptr<Anim> (void)>> ctors = {
		{Env::Sky, [&](){
			return std::make_unique<AnimSky>(*this);
		}},
		{Env::Volcano, [&](){
			return std::make_unique<AnimVolcano>(*this);
		}},
		{Env::Mario, [&](){
			return std::make_unique<AnimMario>(*this);
		}},
		{Env::Overworld, [&](){
			return std::make_unique<AnimOw>(*this);
		}},
		{Env::Beach, [&](){
			return std::make_unique<AnimBeach>(*this);
		}},
		{Env::Doom, [&](){
			return std::make_unique<AnimDoom>(*this);
		}}
	};

	auto got = ctors.find(m_env);
	if (got != ctors.end())
		m_anim = got->second();
}

void Field::playMusic(void)
{
	static const std::map<Env, std::string> musics = {
		{Env::Overworld, "res/music/ow.ogg"},
		{Env::Mario, "res/music/mario.ogg"},
		{Env::Beach, "res/music/beach.ogg"},
		{Env::Doom, "res/music/doom.ogg"},
		{Env::Sky, "res/music/sky heaven.ogg"},
		{Env::Volcano, "res/music/volcano.ogg"},
	};

	m_music.openFromFile(musics.at(m_env));
	m_music.setVolume(world.session.getSfVolume());
	m_music.setLoop(true);
	m_music.play();
}

Field::AnimSky::AnimSky(Field &field) :
	m_field(field)
{
	static const std::vector<irr::core::vector3df> clouds = {
		{-3.0, 4.0, 2.0},
		{-5.0, 3.0, 6.0},
		{-2.0, 1.0, 7.0},
		{-4.0, 2.0, 9.0},
		{17.0, 1.5, 1.0},
		{15.0, 3.4, 2.0},
		{16.0, 1.0, 6.0},
		{19, 2.6, 9.0}
	};

	for (auto &c : clouds)
		m_field.add<Cloud>(c);
}

Field::AnimSky::~AnimSky(void)
{
}

Field::AnimSky::Cloud::Cloud(const irr::core::vector3df &pos) :
	Model("res/models/box.obj", "res/env/sky/wall.png"),
	m_tscale(1.0 - world.session.rand() * 0.5)
{
	setPos(pos);
	setScale(1.0 + world.session.rand() * 2.0);

	bind(world.events.update, [&, pos](auto){
		auto p = pos + irr::core::vector3df(0.0, sin(world.events.update.getTime() * m_tscale * 0.3), 0.0);
		setPos(p);
	});
}

Field::AnimSky::Cloud::~Cloud(void)
{
}

Field::AnimVolcano::AnimVolcano(Field &field)
{
	static const std::vector<irr::core::vector3df> lavas = {
		{-18.0, 0.0, 4.0},
		{32.0, 0.0, 6.5}
	};

	size_t i = 0;
	for (auto &l : lavas)
		field.add<Lava>(l, i++ > 0);
	field.add<Lava>(irr::core::vector3df(23.0, 0.0, -2.0), true, 15.0);
}

Field::AnimVolcano::~AnimVolcano(void)
{
}

Field::AnimVolcano::Lava::Lava(const irr::core::vector3df &pos, bool rot_inv, double scale) :
	Model("res/models/sphere.obj", "res/env/volcano/box.png")
{
	setPos(pos);
	setScale(scale);

	double ts =  scale / 30.0;
	getMaterial(0).getTextureMatrix(0).setTextureScale(30.0 * ts, 30.0 * ts);
	getMaterial(0).TextureLayer->TextureWrapU = irr::video::ETC_REPEAT;
	getMaterial(0).TextureLayer->TextureWrapV = irr::video::ETC_REPEAT;

	bind(world.events.update, [&, rot_inv](auto){
		auto r = irr::core::vector3df(90.0, 0.0, world.events.update.getTime() * (rot_inv ? 1.0 : -1.0));
		setRot(r);
	});
}

Field::AnimVolcano::Lava::~Lava(void)
{
}

Field::AnimMario::AnimMario(Field &field)
{
	static const std::vector<irr::core::vector3df> ts = {
		{-4.0, 0.0, 4.0},
		{-5.0, 2.0, 9.0},
		{-3.5, 3.5, 1.0},
		{17.0, 1.0, 2.0},
		{16.0, 1.5, 9.0},
		{20.0, 3.5, 1.0},
	};

	for (auto &t : ts)
		field.add<Thing>(t);
	field.add<Thing>(irr::core::vector3df(21.0, -1.5, 8.0), true, 10.0);
}

Field::AnimMario::~AnimMario(void)
{
}

Field::AnimMario::Thing::Thing(const irr::core::vector3df &pos, bool custom_scale, double scale) :
	Model("res/models/thing.obj", "res/env/mario/thing.jpg"),
	m_next_blink(0.0),
	m_blink_for(0.0)
{
	setPos(pos);
	if (custom_scale)
		setScale(scale);
	else
		setScale(2.0 + world.session.rand());

	bind(world.events.update, [&, pos](auto delta){
		m_next_blink -= delta;
		if (m_next_blink <= 0.0) {
			m_next_blink = world.session.rand() * 2.0;
			m_blink_for = world.session.rand() * 0.2;
			setMaterialTexture(0, world.session.driver.getTexture("res/env/mario/thing_blink.jpg"));
		}
		if (m_blink_for > 0.0) {
			m_blink_for -= delta;
			if (m_blink_for <= 0.0)
				setMaterialTexture(0, world.session.driver.getTexture("res/env/mario/thing.jpg"));
		}
		auto p = pos + irr::core::vector3df(0.0, sin(world.events.update.getTime() * 0.2), 0.0);
		setPos(p);
	});
}

Field::AnimMario::Thing::~Thing(void)
{
}

Field::AnimOw::AnimOw(Field &field)
{
	static const std::vector<irr::core::vector3df> ts = {
		{-4.0, 1.0, 4.0},
		{-3.75, 1.0, 9.0},
		{-3.5, 1.0, 1.0},
		{17.0, 1.0, 2.0},
		{18.0, 1.0, 5.0},
		{18.0, 1.0, 9.0},
		{19.0, 1.0, 1.0},

		{3.0, 1.0, 12.0},
		{16.0, 1.0, 11.0},
		{10.0, 1.0, 13.0},
		{2.0, 1.0, -4.0},
		{8.0, 1.0, -4.0},
		{12.0, 1.0, -4.5},
	};

	for (auto &t : ts)
		field.add<Grass>(t);
}

Field::AnimOw::~AnimOw(void)
{
}

Field::AnimOw::Grass::Grass(const irr::core::vector3df &pos) :
	Model("res/models/grass.obj", "res/env/ow/grass.jpg")
{
	setPos(pos);
	setScale(2.0);

	auto scale = 1.0 + world.session.rand() * 0.2;
	bind(world.events.update, [&, pos, scale](auto){
		auto t = world.events.update.getTime() * scale;
		auto s = irr::core::vector3df(2.0 + sin(t) * 0.1, 2.0, 2.0 + cos(t) * 0.1);
		setScale(s);
	});
}

Field::AnimOw::Grass::~Grass(void)
{
}

Field::AnimBeach::AnimBeach(Field &field)
{
	static const std::vector<irr::core::vector3df> ts = {
		{0.0, -0.4999, 4.5},
		{14.0, -0.4999, 4.5}
	};

	size_t i = 0;
	for (auto &t : ts)
		field.add<Water>(t, i++ > 0);
}

Field::AnimBeach::~AnimBeach(void)
{
}

Field::AnimBeach::Water::Water(const irr::core::vector3df &pos, bool is_inv) :
	Model("res/models/box.obj", is_inv ? "res/env/beach/wave_inv.jpg" : "res/env/beach/wave.jpg")
{
	setPos(pos);
	setScale(irr::core::vector3df(16.0f, 0.0005f, 16.0f));

	auto ts = 1.0 + world.session.rand() * 0.2;
	bind(world.events.update, [&, pos, is_inv, ts](auto){
		auto t = world.events.update.getTime() * 0.2 * ts;
		auto p = pos + irr::core::vector3df((sin(t) - 1.0) * 5.0 * (!is_inv ? 1.0 : -1.0), 0.0, 0.0);
		setPos(p);
	});
}

Field::AnimBeach::Water::~Water(void)
{
}

Field::AnimDoom::AnimDoom(Field &field)
{
	field.add<DoomGuy>(field);
}

Field::AnimDoom::~AnimDoom(void)
{
}

Field::AnimDoom::DoomGuy::DoomGuy(Field &field) :
	Model("res/models/box.obj", "res/env/doom/guy.jpg"),
	m_field(field),
	m_next_mob(0.0)
{
	irr::core::vector3df s(0.7f, 0.001f, 1.0f);
	setScale(s);
	setPos(irr::core::vector3df(-3.0, 1.0, 5.0));

	bind(world.events.update, [&](auto delta){
		auto t = world.events.update.getTime() / 2.0;
		auto center = irr::core::vector3df(7.0, 1.0, 5.0);
		auto rad = 1.2;
		auto p = center + irr::core::vector3df(cos(t) * 10.0 * rad, 0.0, sin(t) * 20.0 * rad);
		setPos(p);

		m_next_mob -= delta;
		if (m_next_mob < 0.0) {
			m_next_mob = world.session.rand() * 0.1;
			field.add<Imp>(*this);
		}
	});
}

Field::AnimDoom::DoomGuy::~DoomGuy(void)
{
}

Field::AnimDoom::Imp::Imp(Field::AnimDoom::DoomGuy &g) :
	Model("res/models/box.obj", "res/env/doom/imp.jpg"),
	m_life(world.session.rand() * 15.0),
	m_is_dead(false)
{
	irr::core::vector3df s(0.7f, 0.001f, 1.0f);
	setScale(s);

	double x = 5.0;
	double y = 5.0;
	while (x >= 0 && x <= 21.0 && y >= 0 && y <= 11.0) {
		x = (world.session.rand() - 1.0) * 50.0;
		y = (world.session.rand() - 1.0) * 50.0;
	}
	setPos(irr::core::vector3df(x, 1.0, y));

	bind(world.events.update, [&](auto delta){
		m_life -= delta;
		if (m_life < 0.0) {
			if (m_is_dead)
				destroy();
			else {
				m_is_dead = true;
				m_life = 15.0;
				setMaterialTexture(0, world.session.driver.getTexture("res/env/doom/imp_dead.jpg"));
			}
		}

		if (m_is_dead)
			return;
		auto v = (g.getPos() - getPos()).normalize() * delta * 5.0;
		setPos(getPos() + v);
		auto p = getPos();

		auto xmin = -3.0;
		auto xmax = 15.0;
		auto zmin = -1.0;
		auto zmax = 13.5;

		if (p.X >= xmin && p.X <= xmax && p.Z >= zmin && p.Z <= zmax) {
			double min = 99999999.0f;
			double v;

			v = fabs(p.X - xmin);
			if (v < min)
				min = v;
			v = fabs(p.X - xmax);
			if (v < min)
				min = v;
			v = fabs(p.Z - zmin);
			if (v < min)
				min = v;
			v = fabs(p.Z - zmax);
			if (v < min)
				min = v;

			if (min == fabs(p.X - xmin))
				p.X = 0.0f;
			else if (min == fabs(p.X - xmax))
				p.X = xmax;
			else if (min == fabs(p.Z - zmin))
				p.Z = 0.0f;
			else if (min == fabs(p.Z - zmax))
				p.Z = xmax;
		}
		setPos(p);
	});
}

Field::AnimDoom::Imp::~Imp(void)
{
}

}