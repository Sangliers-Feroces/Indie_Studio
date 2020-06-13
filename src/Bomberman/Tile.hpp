#pragma once

#include <map>
#include <iostream>
#include "Model.hpp"

namespace Bomberman {

class Mob;
class Field;

class Tile : public Model
{
public:
	enum class Type {
		Wall,
		Air,
		Box,
		Ground
	};

	Tile(Type type, const irr::core::vector2di &pos, Field &field, int32_t height = 0);
	Tile(std::istream &i, const irr::core::vector2di &pos, Field &field, Type type);
	Tile(std::istream &i, Field &field, Type type);
	Tile(std::istream&, Field&);
	~Tile(void);

	void write(std::ostream&);

	Type getType(void) const;
	void setType(Type type);
	const std::vector<std::reference_wrapper<Mob>>& getMobs(void);

private:
	Field &m_field;
	Type m_type;
	irr::core::vector2di m_pos;
	int32_t m_height;
	std::vector<std::reference_wrapper<Mob>> m_mobs;	// mobs on that tile

	void renderType(void);
	friend Mob;
	void addMob(Mob &mob);
	void removeMob(Mob &mob);
	bool tryRemoveMob(Mob &mob);

	using reader_type = std::function<Mob& (std::istream&, Field&)>;
	using reader_table = std::map<en::util::type_id_t, reader_type>;

	template <typename First, typename ...Args>
	static void genReadersImpl(reader_table &res);

	template <typename ...Args>
	static reader_table genReaders(void)
	{
		reader_table res;

		genReadersImpl<Args...>(res);
		return res;
	}
};

}

#include "Mob.hpp"
#include "Field.hpp"