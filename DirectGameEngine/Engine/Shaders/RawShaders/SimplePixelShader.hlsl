struct VertexOut
{
	float4 iPosH	:	SV_POSITION;
	float2 iTexCoords	:	TEXCOORDS;
};

Texture2D tex;

SamplerState normalSampling;

float4 main(VertexOut pIn) : SV_TARGET
{
	float4 color = tex.Sample(normalSampling, pIn.iTexCoords);
	return color;
}