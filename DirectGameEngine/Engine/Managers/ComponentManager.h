#pragma once

#include <vector>

using ComponentID = std::size_t;

#define MAX_COMPONENTS 50

class ComponentManager
{
public:
	template<typename T>
	auto static GetUniqueComponentID()
	{
		static ComponentID componentID{GetComponentID()};
		return componentID;
	}

private:
	auto static GetComponentID()
	{
		static ComponentID lastComponentID{ 0u };
		return lastComponentID++;
	}

private:
	
};