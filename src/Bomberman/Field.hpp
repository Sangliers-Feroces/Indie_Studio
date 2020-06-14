#pragma once

#include <iostream>
#include <vector>
#include "Engine/World.hpp"
#include "Camera.hpp"
#include "Tile.hpp"


namespace Bomberman {

class Player;

class Field : public en::World
{
public:
	struct PlayerMeta {
		bool is_bot;
		std::string name;

		size_t icon_idx;
	};

	enum class Env {
		Overworld,
		Mario,
		Beach,
		Doom,
		Sky,
		Volcano
	};

	static const std::vector<Env>& getEnvs(void);

	Field(const std::vector<PlayerMeta> &players, Env env = Env::Overworld);
	void init(void);
	void bindPlayer(Player &p);
	std::vector<std::vector<std::reference_wrapper<Tile>>> readTiles(std::istream &i);
	Field(std::istream &i);

	~Field(void);

	Tile& at(const irr::core::vector2di &pos);
	Tile::Type typeAt(const irr::core::vector2di &pos);
	void nuke(const irr::core::vector2di &pos, bool is_simulation = false);
	void genItem(const irr::core::vector2di &pos);

	template <class MobType, typename ...Args>
	MobType& addMob(Args &&...args);



	size_t getWidth(void) const;
	size_t getHeight(void) const;
	const std::string& typeToTexture(Tile::Type type);


	void updateBombMap(void);
	bool isBombed(const irr::core::vector2di &pos);
	bool anySpark(const irr::core::vector2di &pos);

	std::vector<std::reference_wrapper<Player>> getPlayers(void);

	void write(std::ostream&);

private:
	Env m_env;
	std::vector<std::vector<std::reference_wrapper<Tile>>> m_tiles;
	std::vector<std::vector<bool>> m_bombs;
	size_t m_w;
	size_t m_h;
	Camera &m_camera;
	Tile &m_wall;
	size_t m_players_alive;
	std::vector<std::reference_wrapper<Player>> m_players;
	sf::Music m_music;

	class Anim
	{
	public:
		virtual ~Anim(void) = default;
	};

	std::unique_ptr<Anim> m_anim;

	class AnimSky : public Anim
	{
	public:
		AnimSky(Field &field);
		~AnimSky(void) override;

		class Cloud : public Model
		{
		public:
			Cloud(const irr::core::vector3df &pos);
			~Cloud(void);

		private:
			double m_tscale;
		};

	private:
		Field &m_field;
	};

	class AnimVolcano : public Anim
	{
	public:
		AnimVolcano(Field &field);
		~AnimVolcano(void) override;

		class Lava : public Model
		{
		public:
			Lava(const irr::core::vector3df &pos, bool rot_inv, double scale = 30.0);
			~Lava(void);

		private:
			double m_tscale;
		};

	private:
	};

	class AnimMario : public Anim
	{
	public:
		AnimMario(Field &field);
		~AnimMario(void) override;

		class Thing : public Model
		{
		public:
			Thing(const irr::core::vector3df &pos);
			~Thing(void);

		private:
		};

	private:
	};

	static std::string id_to_str(size_t id);

	std::vector<std::vector<Tile::Type>> genField(void);
	std::vector<std::vector<std::reference_wrapper<Tile>>> genTiles(void);
	void addBarrier(void);
	void addAnim(void);
	void playMusic(void);
};

}

#include "Player.hpp"

template <class MobType, typename ...Args>
MobType& Bomberman::Field::addMob(Args &&...args)
{
	auto &s = Mob::getStack();

	s.emplace(*this);
	auto &res = add<MobType>(std::forward<Args>(args)...);
	s.pop();
	return res;
}

