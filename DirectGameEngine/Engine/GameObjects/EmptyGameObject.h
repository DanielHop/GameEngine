#pragma once

#include <memory>

#include "../Components/TransformComponent.h"

struct EmptyGameObject
{
	EmptyGameObject(std::shared_ptr<Entity> e, XMFLOAT3 pos)
	{
		e->AddComponent<TransformComponent>(pos);
	}

	EmptyGameObject(std::shared_ptr<Entity> e, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale)
	{
		e->AddComponent<TransformComponent>(pos, rot, scale);
	}
};