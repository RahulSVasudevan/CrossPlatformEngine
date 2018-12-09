#include "Material.h"
//#include"WICTextureLoader.h"

Material::Material(SimpleVertexShader* vShader, SimplePixelShader* pShader, IRenderer* renderer)
{
	vertexShader = vShader;
	pixelShader = pShader;
	Renderer = renderer;

}

SimpleVertexShader* Material::getvertexShader()
{
	return vertexShader;
}

SimplePixelShader* Material::getpixelShader()
{
	return pixelShader;
}

void Material::LoadTextures()
{
	CreateWICTextureFromFile(dynamic_cast<WinRenderer*>(Renderer)->GetDevice(), dynamic_cast<WinRenderer*>(Renderer)->GetContext(), L"../CommonFiles/Lamborginhi_Aventador_diffuse.jpeg", 0, &SRV);
	D3D11_SAMPLER_DESC sd = {}; // Zeros it out
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // Tri-linear filtering
												 //sd.Filter = D3D11_FILTER_ANISOTROPIC;
												 //sd.MaxAnisotropy = 16;
	sd.MaxLOD = D3D11_FLOAT32_MAX;

	dynamic_cast<WinRenderer*>(Renderer)->GetDevice()->CreateSamplerState(&sd, &Sampler);
}

void Material::DatatoShader()
{
	pixelShader->SetShaderResourceView("wallTexture", SRV);
	pixelShader->SetSamplerState("basicSampler", Sampler);

	pixelShader->CopyAllBufferData();
	pixelShader->SetShader();
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
