#include "BulletScript.h"



BulletScript::BulletScript(XMFLOAT2 vel, float range) : m_vel{vel}, m_range{range}
{
}

void BulletScript::OnTickUpdate(float dt)
{
	transform->pos.x += m_vel.x;
	transform->pos.y += m_vel.y;

	m_distance += m_vel.x;

	if (m_distance >= m_range)
		entity->Die();
}
