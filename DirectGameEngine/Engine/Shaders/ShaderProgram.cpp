#include "ShaderProgram.h"




ShaderProgram::ShaderProgram()
{
}


ShaderProgram::~ShaderProgram()
{
}

HRESULT ShaderProgram::CompileShader(std::string srcFileVertexShader, std::string srcFilePixelShader, ID3D11Device** device)
{
	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif
	std::string fullPath = "C:/Programming/CPP/GameEngine/DirectGameEngine/Debug/";
	std::string fullPathVertex = fullPath + srcFileVertexShader;

	std::string fullPathPixel = fullPath + srcFilePixelShader;

	vsb = m_BasicReader->ReadData(fullPathVertex);
	psb = m_BasicReader->ReadData(fullPathPixel);

	HRESULT hr = (*device)->CreateVertexShader(&(vsb.at(0)),
		vsb.size(),
		NULL,
		&m_vs);

	hr = (*device)->CreatePixelShader(&(psb.at(0)),
		psb.size(),
		NULL,
		&m_ps);

	return hr;
}