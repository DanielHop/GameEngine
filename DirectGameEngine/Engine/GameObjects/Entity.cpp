#include "Entity.h"

Entity::Entity()
{}

Entity::Entity(int id) : m_id{ id }
{

}

bool Entity::HasComponent(ComponentID id)
{
	return componentBitset[id];
}