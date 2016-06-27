#pragma once

#include "Component.h"
#include "../GameObjects/Entity.h"
#include "../Components/TransformComponent.h"

class EntityManager;

class ScriptComponent : public Component
{
public:
	ScriptComponent() {}
	~ScriptComponent() {}

	virtual void InitBase() { transform = entity->GetComponent<TransformComponent>(); Init(); init = true; }

	virtual void OnTickUpdate(float dt) {}
	virtual void LateTickUpdate(float dt) {}

	virtual void OnMouseDown(WPARAM btnState, int x, int y) {}
	virtual void OnMouseUp(WPARAM btnState, int x, int y) {}
	virtual void KeyDown(WPARAM wParam) {}
	virtual void KeyUp(WPARAM wParam) {}

	void SetEntity(Entity* pentity) { this->entity = pentity; }
	void SetManager(EntityManager* pmanager) { this->manager = pmanager; }

	bool IsDead() { return entity->IsDead(); }
public:
	bool init{ false };
protected:
	virtual void Init() {}

private:

protected:
	Entity* entity;
	EntityManager* manager;
	std::shared_ptr<TransformComponent> transform;
};