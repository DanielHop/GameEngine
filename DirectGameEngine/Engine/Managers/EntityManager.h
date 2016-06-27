#pragma once
#include <vector>
#include <Bitset>
#include <memory>
#include <algorithm>
#include <deque>
#include <cassert>

#include "../GameObjects/Entity.h"
#include "../Components/ScriptComponent.h"
#include "../GameObjects/EmptyGameObject.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void Init();
	void OnTickUpdate(float dt);
	void LateTickUpdate(float dt);
	void Update();

	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void KeyDown(WPARAM wParam);
	void KeyUp(WPARAM wParam);

	int AddEntity();
	int GenEmptyGameObject(DirectX::XMFLOAT3 pos = XMFLOAT3{ 0.f, 0.f, 0.f }, XMFLOAT3 rot = XMFLOAT3{ 0.f, 0.f, 0.f }, XMFLOAT3 scale = XMFLOAT3{ 1.f, 1.f, 1.f });
	template<typename T, typename... Targs>
	int AddEntityBlueprint(Targs... args)
	{
		int id = AddEntity();
		T(GetEntity(id), args...);
		return id;
	}
	template<typename T, typename... Targs>
	void AddScriptToEntity(int entID, Targs... args)
	{
		static_assert(std::is_base_of<ScriptComponent, T>::value, "Must be a script");
		std::shared_ptr<T> c(new T{ args... });
		c->SetEntity(GetEntity(entID).get());
		c->SetManager(this);
		scripts.push_back(c);
		int x = 0;
	}
	std::shared_ptr<Entity> GetEntity(int id);

	std::vector<std::shared_ptr<Entity>> GetEntities() { return entities; }

	bool HasEntity(int id);

private:
	int GenEntitityID();
	int prevScriptSize;

private:
	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<ScriptComponent>> scripts;
	std::bitset<5000> ent;
};

