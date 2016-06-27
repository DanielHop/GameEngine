#pragma once

#include "../Components/Component.h"
#include "../Components/TransformComponent.h"
//NEEDS POSITIONCOMPONENT

struct CameraComponent : public Component
{
	CameraComponent(XMFLOAT3 plookAt) : lookAt{ plookAt } { requirements[ComponentManager::GetUniqueComponentID<TransformComponent>()] = 1; }
	XMFLOAT3 lookAt;
};