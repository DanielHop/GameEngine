#pragma once

#include <DirectXMath.h>
#include <bitset>
#include "../Managers/ComponentManager.h"

using ComponentID = std::size_t;

class Entity;
using namespace DirectX;
struct Component
{
	ComponentID componentID;
	std::bitset<50> requirements;
};