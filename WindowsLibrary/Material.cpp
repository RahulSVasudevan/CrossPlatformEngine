#include "Material.h"
//#include"WICTextureLoader.h"

Material::Material(IRenderer* renderer, const wchar_t * obj)
{
	Renderer = renderer;
	
	vertexShader = dynamic_cast<WinRenderer*>(Renderer)->getVertexShader();
	pixelShader = dynamic_cast<WinRenderer*>(Renderer)->getPixelShader();


	filename = obj;
	LoadTextures();
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
	CreateWICTextureFromFile(dynamic_cast<WinRenderer*>(Renderer)->GetDevice(), dynamic_cast<WinRenderer*>(Renderer)->GetContext(), filename, 0, &SRV);
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

/*
void Material::LoadSky()
{
	CreateDDSTextureFromFile(dynamic_cast<WinRenderer*>(Renderer)->GetDevice(), dynamic_cast<WinRenderer*>(Renderer)->GetContext(), DDSFilename, 0, &skySRV);

	// Create a sampler state that holds options for sampling
	// The descriptions should always just be local variables
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX; // Setting this allows for mip maps to work! (if they exist)

											// Ask DirectX for the actual object
	dynamic_cast<WinRenderer*>(Renderer)->GetDevice()->CreateSamplerState(&samplerDesc, &skySampler);
}

*/

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
	SRV->Release();
	Sampler->Release();
	/*this->getSRV()->Release();
	this->getsamplerState()->Release();*/
}
