#include "BatchRenderer2D.h"



BatchRenderer2D::BatchRenderer2D()
{
	m_signature.push_back(ComponentManager::GetUniqueComponentID<SpriteComponent>());
	m_signature.push_back(ComponentManager::GetUniqueComponentID<TransformComponent>());
}


BatchRenderer2D::~BatchRenderer2D()
{
	
}

void BatchRenderer2D::Init(ID3D11Device* device, ID3D11DeviceContext* context)
{
	D3D11_BUFFER_DESC bufferdesc;
	bufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferdesc.ByteWidth = sizeof(VertexData) * RENDERER_MAX_SPRITES * 4;
	bufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferdesc.MiscFlags = 0;
	bufferdesc.StructureByteStride = 0;
	bufferdesc.Usage = D3D11_USAGE_DYNAMIC;

	HRESULT hr = device->CreateBuffer(&bufferdesc, NULL, &m_VB);

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = sizeof(unsigned int) * RENDERER_INDICES;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	int offset = 0;
	unsigned int ibo[RENDERER_INDICES];
	for (unsigned int i = 0; i < RENDERER_INDICES; i += 6)
	{
		ibo[  i  ] = 0 + offset;
		ibo[i + 1] = 1 + offset;
		ibo[i + 2] = 2 + offset;
		ibo[i + 3] = 0 + offset;
		ibo[i + 4] = 2 + offset;
		ibo[i + 5] = 3 + offset;

		offset += 4;
	}
	D3D11_SUBRESOURCE_DATA iData;
	iData.pSysMem = ibo;

	hr = device->CreateBuffer(&indexBufferDesc, &iData, &m_IB);

}

void BatchRenderer2D::Begin(ID3D11DeviceContext* context)
{
	D3D11_MAPPED_SUBRESOURCE vBuffer;
	HRESULT hr = context->Map(m_VB, 0, D3D11_MAP_WRITE_DISCARD, 0, &vBuffer);
	mappedResource = (VertexData*)vBuffer.pData;
}

void BatchRenderer2D::Submit(std::shared_ptr<Entity> e, int i)
{
	auto s = e->GetComponent<SpriteComponent>();
	auto t = e->GetComponent<TransformComponent>();
	XMFLOAT3 pos = t->pos;
	XMFLOAT3 scale = t->scale;

	XMINT2 texCoords = s->texCoords;
	XMFLOAT2 UV = XMFLOAT2((float)texCoords.x * 1.f / 8.f + (float)(texCoords.x + 1)/64.f, (float)texCoords.y * 1.f / 8.f + (float)(texCoords.y + 1) / 64.f);
	float offset = 1.f / 8.f; // 1.f / 256.f;

	VertexData tmp;
	tmp.pos   = XMFLOAT3(pos.x, pos.y - scale.y, pos.z);
	tmp.texCoords = XMFLOAT2(UV.x, UV.y + offset);
	mappedResource[4 * i + 0] = tmp;

	tmp.pos = pos;
	tmp.texCoords = UV;
	mappedResource[4 * i + 1] = tmp;

	tmp.pos = XMFLOAT3(pos.x + scale.x, pos.y, pos.z);
	tmp.texCoords = XMFLOAT2(UV.x + offset, UV.y);
	mappedResource[4 * i + 2] = tmp;

	tmp.pos = XMFLOAT3(pos.x + scale.x, pos.y - scale.y, pos.z);
	tmp.texCoords = XMFLOAT2(UV.x + offset, UV.y + offset);
	mappedResource[4 * i + 3] = tmp;
}

void BatchRenderer2D::End(ID3D11DeviceContext* context)
{
	context->Unmap(m_VB, 0);
}

void BatchRenderer2D::Flush(ID3D11DeviceContext* context, int i)
{
	UINT stride = sizeof(VertexData);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &m_VB, &stride, &offset);
	context->IASetIndexBuffer(m_IB, DXGI_FORMAT_R32_UINT, 0);

	context->DrawIndexed(6 * i, 0, 0);
}