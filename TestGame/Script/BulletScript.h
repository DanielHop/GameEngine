#pragma once

#include <GameEngine.h>

class BulletScript : public ScriptComponent
{
public:
	BulletScript(XMFLOAT2 vel, float range);

	void OnTickUpdate(float dt)override;

private:
	XMFLOAT2 m_vel;
	float m_range, m_distance{0};
};

