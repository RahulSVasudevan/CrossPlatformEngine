#include "Material.h"


Material::Material(SimpleVertexShader* vShader, SimplePixelShader* pShader, ID3D11ShaderResourceView* srv, ID3D11SamplerState* sampler)
{
	vertexShader = vShader;
	pixelShader = pShader;
	SRV = srv;
	Sampler = sampler;

}

SimpleVertexShader* Material::getvertexShader()
{
	return vertexShader;
}

SimplePixelShader* Material::getpixelShader()
{
	return pixelShader;
}

ID3D11ShaderResourceView * Material::getSRV()
{
	return SRV;
}

ID3D11SamplerState * Material::getsamplerState()
{
	return Sampler;
}

Material::~Material()
{

}
