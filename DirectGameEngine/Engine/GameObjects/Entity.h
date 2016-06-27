#pragma once

#include <vector>
#include <memory>
#include <bitset>
#include <windows.h>

#include "../Managers/ComponentManager.h"
#include "../Components/Component.h"

class Entity
{
public:
	Entity();
	Entity(int id);

	template<typename T, typename... Targs>
	std::shared_ptr<T> AddComponent(Targs... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "MUST BE DERIVED FROM COMPONENT");
		std::shared_ptr<T> c(new T{ args... });
		c->componentID = ComponentManager::GetUniqueComponentID<T>();
		componentBitset[ComponentManager::GetUniqueComponentID<T>()] = 1;
		for (int i = 0; i < 50; i++)
		{
			if (c->requirements[i] == 1)

				if (componentBitset[i] == 0)
					MessageBoxA(0, LPCSTR("You need to look at the requirements of this component "), LPCSTR("Component add failure"), 0);
		}
		components.emplace_back(c);

		return c;
	}

	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		for (auto& c : components)
			if (c->componentID == ComponentManager::GetUniqueComponentID<T>())
				return std::static_pointer_cast<T>(c);
		return nullptr;
	}

	
	template<typename T>
	bool HasComponent()
	{
		return componentBitset[ComponentManager::GetUniqueComponentID<T>()];
	}
	bool HasComponent(ComponentID id);

	void SetID(int id)	{ m_id		= id;	}
	void Die()			{ m_isAlive = false;}

	int GetID()			{ return m_id;		}
	bool IsDead()		{ return m_isAlive; }
private:
	int m_id;
	bool m_isAlive{ true };

	std::vector<std::shared_ptr<Component>>			components;
	std::bitset<MAX_COMPONENTS> componentBitset;
};
