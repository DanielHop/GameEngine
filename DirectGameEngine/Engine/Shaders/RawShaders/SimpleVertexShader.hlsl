cbuffer cbProjMatrix
{
	float4x4 gProjMatrix;
}; 

cbuffer cbViewMatrix
{
	float4x4 gViewMatrix;
};

struct VertexIn
{
	float3 iPos : POSITION;
	float3 iNormal : NORMAL;
	float2 iTexCoords : TEXCOORDS;
};

struct VertexOut
{
	float4 oPosH	:	SV_POSITION;
	float2 oTexCoords	:	TEXCOORDS;
};

VertexOut main(VertexIn vIn)
{
	VertexOut vOut;

	vOut.oPosH = mul(float4(vIn.iPos, 1.0f), gViewMatrix);
	vOut.oPosH = mul(vOut.oPosH, gProjMatrix);
	vOut.oTexCoords = vIn.iTexCoords;
	return vOut;
}