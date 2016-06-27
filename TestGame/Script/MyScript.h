#pragma once

#include <windows.h>

#include <GameEngine.h>

#include "BulletScript.h"

class MyScript : public ScriptComponent
{
public:
	void Init()override;
	void OnMouseDown(WPARAM btnState, int x, int y)override;
	void Shoot();
	void OnMouseUp(WPARAM btnState, int x, int y)override;
	void KeyDown(WPARAM wParam)override;
	void KeyUp(WPARAM wParam)override;
	void OnTickUpdate(float dt)override;

private:
	XMFLOAT3 vel;
	int time{ 0 };
	bool isDown{ false };
	int moveY{ 0 }, moveX{ 0 };
};