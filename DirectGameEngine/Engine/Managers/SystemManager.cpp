#include "SystemManager.h"



SystemManager::SystemManager()
{
}


SystemManager::~SystemManager()
{
}

void SystemManager::Init()
{
	for (auto& s : m_systems)
		s->Init();

	m_isInit = true;
}

void SystemManager::OnTickUpdate(std::vector<std::shared_ptr<Entity>> entities, float dt)
{
	if (!m_isInit)Init();
	for (auto& system : m_systems) {
		if (system->m_type == EMPTY_UPDATE)
			system->EmptyUpdate();
		else
			if (system->m_type != RENDER_UPDATE)
			{
				std::vector<std::shared_ptr<Entity>> pushBackEntities;
				auto signature = system->GetSignature();
				for (auto ent : entities)
				{
					bool add = true;
					for (auto i : signature)
						if (!ent->HasComponent(i))
						{
							add = false;
						}
					if (add)pushBackEntities.push_back(ent);
				}
				system->OnTickUpdate(pushBackEntities, dt);
			}
	}
}

void SystemManager::RenderUpdate(std::vector<std::shared_ptr<Entity>> entities, ID3D11Device* device, ID3D11DeviceContext* context)
{
	for (auto& system : m_systems) {
		if (system->m_type != ON_TICK_UPDATE && system->m_type != EMPTY_UPDATE)
		{
			std::vector<std::shared_ptr<Entity>> pushBackEntities;
			auto signature = system->GetSignature();
			for (auto ent : entities)
			{
				bool add = true;
				for (auto i : signature)
					if (!ent->HasComponent(i))
					{
						add = false;
					}
				if (add)pushBackEntities.push_back(ent);
			}
			system->RenderUpdate(pushBackEntities, device, context);
		}
	}

	for (auto& r : m_renderer)
	{
		std::vector<std::shared_ptr<Entity>> pushBackEntities;
		auto signature = r->GetSignature();
		for (auto ent : entities)
		{
			bool add = true;
			for (auto i : signature)
				if (!ent->HasComponent(i))
				{
					add = false;
				}
			if (add)pushBackEntities.push_back(ent);
		}
		r->Render(pushBackEntities, context);
	}
}

void SystemManager::Shutdown()
{
	for (auto& s : m_systems)
		s->Shutdown();

	for (auto& r : m_renderer)
		r->Shutdown();

	for (auto s : m_shaders)
		s->CleanUp();
}