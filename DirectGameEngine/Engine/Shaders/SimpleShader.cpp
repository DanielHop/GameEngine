#include "SimpleShader.h"



SimpleShader::SimpleShader()
{
}


SimpleShader::~SimpleShader()
{
}

void SimpleShader::InitShader(ID3D11Device* device, ID3D11DeviceContext* context, const wchar_t* TexurefileName)
{
	HRESULT hr = CompileShader("SimpleVertexShader.cso", "SimplePixelShader.cso", &device);
	context->VSSetShader(m_vs, NULL, NULL);
	context->PSSetShader(m_ps, NULL, NULL);

	D3D11_INPUT_ELEMENT_DESC elementDesc[]
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORDS",	 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	ID3D11InputLayout* layout;

	hr = device->CreateInputLayout(elementDesc, 3, &(vsb.at(0)),
		vsb.size(), &layout);

	context->IASetInputLayout(layout);

	layout->Release();

	DirectX::XMFLOAT4X4 ProjStoreMatrix;

	DirectX::XMMATRIX projMatrx = DirectX::XMMatrixOrthographicLH(16.f/9.f * 2.f, 2.f, 0.1f, 1000);
	DirectX::XMStoreFloat4x4(&ProjStoreMatrix, projMatrx);
	LoadMatrix(ProjStoreMatrix, 0, device, context);

	DirectX::XMStoreFloat4x4(&ProjStoreMatrix, DirectX::XMMatrixIdentity());
	LoadMatrix(ProjStoreMatrix, 1, device, context);

	ID3D11ShaderResourceView* texture;
	ID3D11Resource* tmp;
	hr = DirectX::CreateWICTextureFromFile(device, TexurefileName, &tmp, &texture);
	context->PSSetShaderResources(0, 1, &texture);

	texture->Release();
	tmp->Release();

	D3D11_SAMPLER_DESC sd;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.Filter = D3D11_FILTER_ANISOTROPIC;
	sd.MipLODBias = 0;
	sd.MaxAnisotropy = 4;

	ID3D11SamplerState* ss;
	hr = device->CreateSamplerState(&sd, &ss);

	context->PSSetSamplers(0, 1, &ss);

	ss->Release();

	D3D11_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));
	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	//blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	ID3D11BlendState* bs;
	hr = device->CreateBlendState(&blendStateDescription, &bs);

	float blendFactor[4];


	// Setup the blend factor.
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	context->OMSetBlendState(bs, blendFactor, 0xffffff);
	bs->Release();
}

void SimpleShader::LoadMatrix(DirectX::XMFLOAT4X4 matrix, int location, ID3D11Device* device, ID3D11DeviceContext* context)
{
	ID3D11Buffer*   cBuffer = NULL;

	ConstantMatrixBuffer buffer;
	buffer.proj = matrix;

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.ByteWidth = sizeof(ConstantMatrixBuffer);
	cbDesc.Usage = D3D11_USAGE_IMMUTABLE;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &buffer;

	HRESULT hr  = device->CreateBuffer(&cbDesc, &data, &cBuffer);

	context->VSSetConstantBuffers(location, 1, &cBuffer);

	cBuffer->Release();
}

void SimpleShader::CleanUp()
{
	if(m_ps)
		m_ps->Release();
	if(m_vs)
		m_vs->Release();
}