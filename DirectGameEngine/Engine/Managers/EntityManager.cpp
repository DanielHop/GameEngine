#include "EntityManager.h"



EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

void EntityManager::Init()
{
	for (auto s : scripts)
		if(!s->init)
			s->InitBase();

	prevScriptSize = scripts.size();
}

void EntityManager::OnTickUpdate(float dt)
{
	for (unsigned int x = 0; x < scripts.size(); x++)
		if (scripts.at(x)->init)
			scripts.at(x)->OnTickUpdate(dt);
}

void EntityManager::LateTickUpdate(float dt)
{
	for (auto s : scripts)
		if (s->init)
			s->LateTickUpdate(dt);
}

void EntityManager::OnMouseDown(WPARAM btnState, int x, int y)
{
	for (unsigned int x = 0; x < scripts.size(); x++)
		if (scripts.at(x)->init)
			scripts.at(x)->OnMouseDown(btnState, x, y);
}

void EntityManager::OnMouseUp(WPARAM btnState, int x, int y)
{
	for (auto s : scripts)
		if (s->init)
			s->OnMouseUp(btnState, x, y);
}

void EntityManager::KeyDown(WPARAM wParam)
{
	for (auto s : scripts)
		if(s->init)
			s->KeyDown(wParam);
}

void EntityManager::KeyUp(WPARAM wParam)
{
	for (auto s : scripts)
		s->KeyUp(wParam);
}

void EntityManager::Update()
{
	scripts.erase(std::remove_if(std::begin(scripts), std::end(scripts),
		[](std::shared_ptr<ScriptComponent>& script)
	{
		return !script->IsDead();
	}), std::end(scripts));

	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](std::shared_ptr<Entity>& mEntity)
	{
		return !mEntity->IsDead();
	}), std::end(entities));

	if (prevScriptSize != scripts.size())
		Init();
}

int EntityManager::AddEntity()
{
	int id = GenEntitityID();

	std::shared_ptr<Entity>e(new Entity(id));
	entities.push_back(e);

	return entities.back()->GetID();
}
std::shared_ptr<Entity> EntityManager::GetEntity(int id)
{
	assert(HasEntity(id)); 
	for (auto e : entities)
		if (e->GetID() == id) 
			return e;
	return entities.at(0);
}

bool EntityManager::HasEntity(int id)
{
	for (auto e : entities)
		if (e->GetID() == id) 
			return true; 
	
	return false;
}

int EntityManager::GenEmptyGameObject(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot, DirectX::XMFLOAT3 scale)
{
	return AddEntityBlueprint<EmptyGameObject>(pos, rot, scale);
}

int EntityManager::GenEntitityID()
{
	int x = 0;
	while (true)
	{
		if (ent[x] == 0)
		{
			ent.set(x, 1);
			return x;
		}
		x++;
	}
	return -1;
}