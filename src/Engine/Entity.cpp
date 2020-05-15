#include "Entity.hpp"

namespace Engine {

Entity::Entity(const Context &ctx) :
	world(ctx.world),
	m_parent(ctx.parent)
{
}

Entity::~Entity(void)
{
}

}