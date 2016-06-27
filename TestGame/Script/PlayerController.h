#pragma once

#include <GameEngine.h>

class PlayerController : public ScriptComponent
{
public:
	PlayerController();
	~PlayerController();

	void Init() override;
	void LateTickUpdate(float dt)override;
	void KeyDown(WPARAM wParam)override;
	void KeyUp(WPARAM wParam)override;

private:
	float speed;
	bool shouldMoveDown, shouldMoveUp;
};

