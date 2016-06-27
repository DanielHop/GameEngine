#include "Test.h"

struct Vertex
{
	XMFLOAT3 pos;
	XMFLOAT4 colour;
};

void Test::InitGame()
{
	m_systemManager->AddShader<SimpleShader>("SimpleShader 1", m_d3dDevice, m_d3dImmediateContext, L"C:/Programming/CPP/GameEngine/DirectGameEngine/TestGame/Res/Textures8x8.png");

	m_systemManager->Addrenderer<BatchRenderer2D>(m_d3dDevice, m_d3dImmediateContext);

	m_systemManager->AddSystem<CameraSystem>((m_systemManager->GetShader<SimpleShader>("SimpleShader 1")));
	m_systemManager->AddSystem<InputSystem>();

	SetCameraPosition(XMFLOAT3{ 0.f, 0.f, -1.f });

	auto playerPaddle = m_entityManager->AddEntityBlueprint<Sprite>(XMFLOAT3{ 0.f, 0.f, 0.f }, XMFLOAT3{ 0.25f, 1.5f, 1.0f }, XMINT2{ 0, 1 });
	m_entityManager->AddScriptToEntity<PlayerController>(playerPaddle);

	auto npcController = m_entityManager->GenEmptyGameObject();

}

void Test::GameShutdown()
{

}