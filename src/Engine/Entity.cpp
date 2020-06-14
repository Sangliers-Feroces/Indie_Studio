#include "Entity.hpp"

namespace Engine {

Entity::Entity(void) :
	world(getStack().top().world),
	m_parent(getStack().top().parent),
	m_irr_node(getStackScene().addEmptySceneNode(getStackParentNode())),
	m_to_destroy(false)
{
}

Entity::Entity(irr::scene::ISceneNode *irrnode) :
	world(getStack().top().world),
	m_parent(getStack().top().parent),
	m_irr_node(irrnode),
	m_to_destroy(false)
{
}

Entity::Entity(const Context &ctx, irr::scene::ISceneManager &sceneMgr) :
	world(ctx.world),
	m_parent(ctx.parent),
	m_irr_node(sceneMgr.addEmptySceneNode(m_parent ? &*m_parent->m_irr_node : nullptr)),
	m_to_destroy(false)
{
}

Entity::~Entity(void)
{
}

std::stack<Entity::Context>& Entity::getStack(void)
{
	static thread_local std::stack<Entity::Context> res;

	return res;
}

World& Entity::getStackWorld(void)
{
	return getStack().top().world;
}

irr::scene::ISceneManager& Entity::getStackScene(void)
{
	return getStack().top().world.m_irr_scene;
}

irr::scene::ISceneNode* Entity::getStackParentNode(void)
{
	auto &p = getStack().top().parent;

	if (p)
		return &*p->m_irr_node;
	else
		return nullptr;
}

util::unique_set<Entity>& Entity::getChildren(void)
{
	return m_children;
}

void Entity::destroy(void)
{
	m_to_destroy = true;
}

bool Entity::destroyIfMarked(void)
{
	if (!m_to_destroy)
		return false;

	if (m_parent == nullptr)
		throw std::runtime_error("Can't destroy root entity");

	auto &c = m_parent->m_children;
	auto got = c.find(*this);
	if (got == c.end())
		throw std::runtime_error("Can't find entity in its own parent");
	c.erase(got);
	return true;
}

void Entity::collectGarbage(void)
{
	while (tryDestroyChild());
	for (auto &c : m_children)
		c.collectGarbage();
}

bool Entity::tryDestroyChild(void)
{
	for (auto &c : m_children)
		if (c.destroyIfMarked())
			return true;
	return false;
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

void Entity::setScale(double scale)
{
	setScale(irr::core::vector3df(scale));
}

void Entity::setScale(const irr::core::vector3df& scale)
{
	m_irr_node->setScale(scale);
}

void Entity::updateAbsolutePosition(void)
{
	m_irr_node->updateAbsolutePosition();
}

irr::video::SMaterial& Entity::getMaterial(const irr::u32& num)
{
	return (m_irr_node.get().getMaterial(num));
}

irr::u32 Entity::getMaterialCount(void) const
{
	return (m_irr_node.get().getMaterialCount());
}

void Entity::setMaterialFlag(irr::video::E_MATERIAL_FLAG flag, bool newvalue)
{
	m_irr_node.get().setMaterialFlag(flag, newvalue);
}

void Entity::setMaterialTexture(irr::u32 textureLayer, irr::video::ITexture *texture)
{
	m_irr_node.get().setMaterialTexture(textureLayer, texture);
}

void Entity::setMaterialType(irr::video::E_MATERIAL_TYPE newtype)
{
	m_irr_node.get().setMaterialType(newtype);
}

}