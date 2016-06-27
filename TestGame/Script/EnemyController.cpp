#include "EnemyController.h"



EnemyController::EnemyController(float EPS) : m_EPS{EPS}
{
	m_timeCount = 0;
	count = 0;
}


EnemyController::~EnemyController()
{
}

void EnemyController::OnTickUpdate(float dt)
{

	m_timeCount += dt;
	if (m_timeCount > 1.f)
	{
		auto e = manager->AddEntityBlueprint<Sprite>(transform->pos, XMFLOAT3{ 1.f, 1.f, 1.f }, XMINT2{ 1, 0 });
		count++;
		m_timeCount = 0;
	}
	
}
