#pragma once

#include "../Core/DXApp.h"

#include "../GameObjects/Camera.h"

#include "../Managers/EntityManager.h"
#include "../Managers/SystemManager.h"
#include "../Managers/InputManager.h"

class SimpleGameApp : public DXApp
{
public:
	SimpleGameApp(HINSTANCE hInstance, int cmdShow) : DXApp{ hInstance, cmdShow } {}
	~SimpleGameApp() {}

	void SetCameraPosition(XMFLOAT3 pos);

private:
	virtual void InitGame() {}
	
	void PreInit()override;
	void LateInit()override;
	void OnTickUpdate(float dt)override;
	void RenderUpdate()override;
	void ShutdownLocal()override;

	void OnMouseDown(WPARAM btnState, int x, int y)override;
	void OnMouseUp(WPARAM btnState, int x, int y)override;
	void KeyDown(WPARAM wParam)override;
	void KeyUp(WPARAM wParam)override;
	virtual void GameShutdown() {}

protected:
	std::unique_ptr<EntityManager>	m_entityManager{ new EntityManager() };
	std::unique_ptr<SystemManager>	m_systemManager{ new SystemManager() };
	int m_camera;
};