#pragma once

#include <memory>

#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

struct Sprite
{
	Sprite(std::shared_ptr<Entity> e, XMFLOAT3 pos, XMINT2 UV)
	{
		e->AddComponent<TransformComponent>(pos);
		e->AddComponent<SpriteComponent>(SpriteComponent{UV});
	}

	Sprite(std::shared_ptr<Entity> e, XMFLOAT3 pos, XMFLOAT3 size, XMINT2 UV)
	{
		e->AddComponent<TransformComponent>(pos, XMFLOAT3{ 0.f, 0.f, 0.f }, size);
		e->AddComponent<SpriteComponent>(SpriteComponent{UV});
	}
};