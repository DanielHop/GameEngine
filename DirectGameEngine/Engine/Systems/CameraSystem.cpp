#include "CameraSystem.h"

CameraSystem::~CameraSystem()
{
}

void CameraSystem::Init()
{
	m_signature.push_back(ComponentManager::GetUniqueComponentID<CameraComponent>());
	m_signature.push_back(ComponentManager::GetUniqueComponentID<TransformComponent>());
}

void CameraSystem::RenderUpdate(std::vector<std::shared_ptr<Entity>> entities, ID3D11Device* device, ID3D11DeviceContext* context)
{
	if (entities.size() == 0)return;
	auto e = entities.front()->GetComponent<CameraComponent>();
	auto p = entities.front()->GetComponent<TransformComponent>();
	DirectX::XMMATRIX cMatrix = DirectX::XMMatrixLookAtLH(XMLoadFloat3(&(p->pos)), XMLoadFloat3(&(e->lookAt)), DirectX::XMVectorSet(0.f, 1.f, 0.f, 1.f));
	XMFLOAT4X4 viewMatrix;
	DirectX::XMStoreFloat4x4(&viewMatrix, cMatrix);
	m_shader->LoadMatrix(viewMatrix, 1, device, context);
}

void CameraSystem::Shutdown()
{
}