#include "World.hpp"

namespace Engine {

World::World(void) :
	Entity(Entity::Context(*this, nullptr), *getStack().top().get().getSceneManager()),
	m_irr_device(getStack().top()),
	driver(*getStack().top().get().getVideoDriver()),
	m_irr_scene(*getStack().top().get().getSceneManager())
{
}

World::~World(void)
{
}

std::stack<std::reference_wrapper<irr::IrrlichtDevice>>& World::getStack(void)
{
	static thread_local std::stack<std::reference_wrapper<irr::IrrlichtDevice>> res;

	return res;
}

irr::scene::IAnimatedMesh& World::getMesh(const std::string &path)
{
	return util::ptr_to_ref(m_irr_scene.getMesh(path.c_str()));
}

}