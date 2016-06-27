#include "PlayerController.h"

PlayerController::PlayerController()
{
	shouldMoveDown = false;
	shouldMoveUp = false;
}


PlayerController::~PlayerController()
{
}

void PlayerController::Init()
{
	speed = 0.2f;
	transform->pos.x = -10.f;
	transform->pos.y = 0.f;
	transform->pos.z = 5.f;
}

void PlayerController::LateTickUpdate(float dt)
{
	float finalSpeed = 0;
	float boundaries = 5.8f;
	if (shouldMoveUp && transform->pos.y < 5.8f)
		finalSpeed += speed;

	if (shouldMoveDown && transform->pos.y > -5.8f + transform->scale.y)
		finalSpeed -= speed;

	transform->pos.y += finalSpeed;
}

void PlayerController::KeyDown(WPARAM wParam)
{
	if (wParam == 'W')
		shouldMoveUp = true;
	if (wParam == 'S')
		shouldMoveDown = true;
}

void PlayerController::KeyUp(WPARAM wParam)
{
	if (wParam == 'W')
		shouldMoveUp = false;
	if (wParam == 'S')
		shouldMoveDown = false;
}