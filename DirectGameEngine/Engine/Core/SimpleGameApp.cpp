#include "SimpleGameapp.h"

void SimpleGameApp::PreInit()
{
	m_camera = m_entityManager->AddEntityBlueprint<Camera>(XMFLOAT3{ 0.f, 0.f, 0.f });
}

void SimpleGameApp::LateInit()
{
	m_entityManager->Init();
}

void SimpleGameApp::OnTickUpdate(float dt)
{
	m_entityManager->OnTickUpdate(dt);
	m_systemManager->OnTickUpdate(m_entityManager->GetEntities(), dt);
	m_entityManager->LateTickUpdate(dt);
	m_entityManager->Update();
}

void SimpleGameApp::RenderUpdate()
{
	m_systemManager->RenderUpdate(m_entityManager->GetEntities(), m_d3dDevice, m_d3dImmediateContext);
}

void SimpleGameApp::ShutdownLocal()
{
	GameShutdown();
	m_systemManager->Shutdown();
}

void SimpleGameApp::SetCameraPosition(XMFLOAT3 pos)
{
	m_entityManager->GetEntity(m_camera)->GetComponent<TransformComponent>()->pos = pos;
}

void SimpleGameApp::OnMouseDown(WPARAM btnState, int x, int y)
{
	m_entityManager->OnMouseDown(btnState, x, y);
}

void SimpleGameApp::OnMouseUp(WPARAM btnState, int x, int y)
{
	m_entityManager->OnMouseUp(btnState, x, y);
}

void SimpleGameApp::KeyDown(WPARAM wParam)
{
	m_entityManager->KeyDown(wParam);
}

void SimpleGameApp::KeyUp(WPARAM wParam)
{
	m_entityManager->KeyUp(wParam);
}