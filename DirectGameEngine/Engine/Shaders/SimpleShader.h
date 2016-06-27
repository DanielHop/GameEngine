#pragma once
#include <string>
#include <DirectXMath.h>
#include <WICTextureLoader.h>

#include "../Shaders/ShaderProgram.h"

struct ConstantBufferPerFrame
{
	DirectX::XMFLOAT4X4 view;
};

struct ConstantBufferInit
{
	DirectX::XMFLOAT4X4 proj;
};

struct ConstantMatrixBuffer
{
	DirectX::XMFLOAT4X4 proj;
};

class SimpleShader :
	public ShaderProgram
{
public:
	SimpleShader();
	~SimpleShader();

	void InitShader(ID3D11Device* device, ID3D11DeviceContext* context, const wchar_t* TexurefileName)override;
	void LoadMatrix(DirectX::XMFLOAT4X4 matrix, int location, ID3D11Device* device, ID3D11DeviceContext* context);
	void CleanUp()override;
};

