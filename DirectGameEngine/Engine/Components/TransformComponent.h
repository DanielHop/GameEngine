#pragma once

#include "../Components/Component.h"

struct TransformComponent : public Component
{
	TransformComponent(XMFLOAT3 ppos, XMFLOAT3 prot = XMFLOAT3{ 0.f, 0.f, 0.f }, XMFLOAT3 pscale = XMFLOAT3{ 1.f, 1.f, 1.f }) :pos{ ppos }, scale{ pscale }, rot{ prot } {}
	XMFLOAT3 pos, rot, scale;
};