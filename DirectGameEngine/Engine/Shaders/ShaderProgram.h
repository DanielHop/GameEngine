#pragma once

#include <wchar.h>
#include <memory>
#include <d3d11.h>
#include <d3dcompiler.h>

#include "../Util/BasicReader.h"


class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	virtual void InitShader(ID3D11Device* device, ID3D11DeviceContext* context, const wchar_t* TexurefileName) = 0;
	virtual void CleanUp() = 0;

	auto GetVsShader() { return m_vs; }
	auto GetVsVectorPointer() { return &vsb; }
protected:
	HRESULT CompileShader(std::string srcFileVertexShader, std::string srcFilePixelShader, ID3D11Device** device);

public:
	std::string name;

protected:
	ID3D11VertexShader* m_vs;
	ID3D11PixelShader* m_ps;
	ID3DBlob* b1, *b2;

	std::vector<uint8_t> vsb, psb;
	std::unique_ptr<BasicReader>m_BasicReader{ new BasicReader() };
};

