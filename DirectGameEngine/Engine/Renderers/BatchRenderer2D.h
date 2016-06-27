#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

#include <bitset>
#include <vector>
#include <deque>

#include "../GameObjects/Entity.h"
#include "../Renderers/Renderer.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

struct VertexData
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 texCoords;
};

#define RENDERER_MAX_SPRITES 2000
#define RENDERER_SPRITE_SIZE sizeof(VertexData)
#define RENDERER_MAX_SPRITES_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_MAX_VERTEXDATA RENDERER_MAX_SPRITES * 4
#define RENDERER_INDICES RENDERER_MAX_SPRITES * 6

class BatchRenderer2D : public Renderer
{
public:
	BatchRenderer2D();
	~BatchRenderer2D();

	void Init(ID3D11Device* device, ID3D11DeviceContext* context)override;

private:
	void Begin(ID3D11DeviceContext* context)override;
	void Submit(std::shared_ptr<Entity> e, int i)override;
	void End(ID3D11DeviceContext* context)override;

	void Flush(ID3D11DeviceContext* context, int nSprites)override;

private:
	VertexData* mappedResource;
};

