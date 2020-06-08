/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityGuiGui
*/

#include "EntityGui.hpp"

namespace Engine {

EntityGui::EntityGui(void) :
	world(getStack().top().world),
	m_parent(getStack().top().parent),
	m_irr_node(getStackScene().addEmptySceneNode(getStackParentNode()))
{
}

EntityGui::EntityGui(irr::scene::ISceneNode *irrnode) :
	world(getStack().top().world),
	m_parent(getStack().top().parent),
	m_irr_node(irrnode)
{
}

EntityGui::EntityGui(const Context &ctx, irr::scene::ISceneManager &sceneMgr) :
	world(ctx.world),
	m_parent(ctx.parent),
	m_irr_node(sceneMgr.addEmptySceneNode(m_parent ? &*m_parent->m_irr_node : nullptr))
{
}

EntityGui::~EntityGui(void)
{
}

std::stack<EntityGui::Context>& EntityGui::getStack(void)
{
	static thread_local std::stack<EntityGui::Context> res;

	return res;
}

EntityGuiWorld& EntityGui::getStackWorld(void)
{
	return getStack().top().world;
}

irr::scene::ISceneManager& EntityGui::getStackScene(void)
{
	return getStack().top().world.m_irr_scene;
}

irr::scene::ISceneNode* EntityGui::getStackParentNode(void)
{
	auto &p = getStack().top().parent;

	if (p)
		return &*p->m_irr_node;
	else
		return nullptr;
}

void EntityGui::destroy(void)
{
	if (m_parent == nullptr)
		throw std::runtime_error("Can't destroy root EntityGui");

	auto &c = m_parent->m_children;
	auto got = c.find(*this);
	if (got == c.end())
		throw std::runtime_error("Can't find EntityGui in its own parent");
	c.erase(got);
}

const irr::video::SMaterial& EntityGui::getMaterial(const irr::u32& num)
{
	return (m_irr_node.get().getMaterial(num));
}

const irr::u32 EntityGui::getMaterialCount() const
{
	return (m_irr_node.get().getMaterialCount());
}

void EntityGui::setMaterialFlag(irr::video::E_MATERIAL_FLAG flag, bool newvalue)
{
	m_irr_node.get().setMaterialFlag(flag, newvalue);
}

void EntityGui::setMaterialTexture(irr::u32 textureLayer, irr::video::ITexture *texture)
{
	m_irr_node.get().setMaterialTexture(textureLayer, texture);
}

void EntityGui::setMaterialType(irr::video::E_MATERIAL_TYPE newtype)
{
	m_irr_node.get().setMaterialType(newtype);
}

}