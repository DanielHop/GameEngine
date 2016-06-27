#pragma once

#include <memory>
#include "../GameObjects/Entity.h"
#include "../Components/TransformComponent.h"
#include "../Components/CameraComponent.h"

struct Camera
{
	Camera(std::shared_ptr<Entity> e, XMFLOAT3 pos, XMFLOAT3 lookAt = XMFLOAT3{ 0.f, 0.f, 0.f })
	{
		e->AddComponent<TransformComponent>(pos);
		e->AddComponent<CameraComponent>(lookAt);
	}
};