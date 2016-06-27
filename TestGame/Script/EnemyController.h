#pragma once

#include <GameEngine.h>

class EnemyController : public ScriptComponent
{
public:
	EnemyController(float EPS);
	~EnemyController();
	
	void OnTickUpdate(float dt)override;
private:
	float m_timeCount, m_EPS;
	int count;
};