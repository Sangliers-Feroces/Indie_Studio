#include "Entity.hpp"

namespace Engine {

Entity::Entity(const Context &ctx) :
	world(ctx.world),
	m_parent(ctx.parent),
	m_irr_node(world.m_irr_scene.addEmptySceneNode(m_parent ? &*m_parent->m_irr_node : nullptr))
{
}

Entity::Entity(const Context &ctx, irr::scene::ISceneManager &sceneMgr) :
	world(ctx.world),
	m_parent(ctx.parent),
	m_irr_node(sceneMgr.addEmptySceneNode(m_parent ? &*m_parent->m_irr_node : nullptr))
{
}

Entity::~Entity(void)
{
}

void Entity::destroy(void)
{
	if (m_parent == nullptr)
		throw std::runtime_error("Can't destroy root entity");

	auto &c = m_parent->m_children;
	auto got = c.find(*this);
	if (got == c.end())
		throw std::runtime_error("Can't find entity in its own parent");
	c.erase(got);
}

const irr::core::vector3df& Entity::getPos(void) const
{
	return m_irr_node->getPosition();
}

const irr::core::vector3df& Entity::getRot(void) const
{
	return m_irr_node->getRotation();
}

const irr::core::vector3df& Entity::getScale(void) const
{
	return m_irr_node->getScale();
}

void Entity::setPos(const irr::core::vector3df& pos)
{
	m_irr_node->setPosition(pos);
}

void Entity::setRot(const irr::core::vector3df& rot)
{
	m_irr_node->setRotation(rot);
}

void Entity::setScale(const irr::core::vector3df& scale)
{
	m_irr_node->setScale(scale);
}

}