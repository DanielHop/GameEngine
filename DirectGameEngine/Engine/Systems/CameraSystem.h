#pragma once

#include <DirectXMath.h>

#include "../Shaders/SimpleShader.h"
#include "../Systems/System.h"
#include "../Components/CameraComponent.h"
#include "../Components/TransformComponent.h"

class CameraSystem : public System
{
public:
	CameraSystem(std::shared_ptr<SimpleShader> shader) : m_shader{ shader } { m_type = RENDER_UPDATE; }
	~CameraSystem();

	void Init()override;
	void RenderUpdate(std::vector<std::shared_ptr<Entity>> entities, ID3D11Device* device, ID3D11DeviceContext* context)override;
	void Shutdown() override;

private:
	std::shared_ptr<SimpleShader> m_shader;
};

