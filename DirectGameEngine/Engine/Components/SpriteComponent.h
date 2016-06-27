#pragma once

#include "../Components/Component.h"
#include "../Components/TransformComponent.h"
//NEEDS POSITIONCOMPONENT

struct SpriteComponent : Component
{
	SpriteComponent(XMINT2 ptexCoords) : texCoords{ ptexCoords }
	{ requirements[ComponentManager::GetUniqueComponentID<TransformComponent>()] = 1; 	}
	XMINT2 texCoords;
};