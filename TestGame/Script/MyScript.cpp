#include "MyScript.h"

void MyScript::Init()
{
	vel =  XMFLOAT3{0.01f, 0.01f, 0.f};
}

void MyScript::OnTickUpdate(float dt)
{
	transform->pos.y += 0.1f * moveY;
	transform->pos.x += 0.1f * moveX;
}

void MyScript::OnMouseDown(WPARAM btnState, int x, int y)
{
	Shoot();
}

void MyScript::Shoot()
{
	auto b = manager->AddEntityBlueprint<Sprite>(transform->pos, XMFLOAT3{ 0.2f, 0.2f, 0.2f}, XMINT2{ 0, 0 });
	manager->AddScriptToEntity<BulletScript>(b, XMFLOAT2(1, 0), 20.f);
}

void MyScript::OnMouseUp(WPARAM btnState, int x, int y)
{
}

void MyScript::KeyDown(WPARAM wParam)
{
	if (wParam == 'W')
		moveY = 1;
	if (wParam == 'S')
		moveY = -1;

	if (wParam == 'D')
		moveX = 1;
	if (wParam == 'A')
		moveX = -1;
}

void MyScript::KeyUp(WPARAM wParam)
{
	if (wParam == 'W' && moveY == 1)
		moveY = 0;
	if (wParam == 'S'&& moveY == -1)
		moveY = 0;

	if (wParam == 'D' && moveX == 1)
		moveX = 0;
	if (wParam == 'A'&& moveX == -1)
		moveX = 0;

}