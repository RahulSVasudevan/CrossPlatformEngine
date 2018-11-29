
#include "GameEntity.h"



mat4x4 GameEntity::setTranslation(float x, float y, float z)
{
	wmTrans = translate(mat4(1.0f), vec3(x, y, z));
	
	this->updateWorld();
	return wmTrans;
}

mat4x4 GameEntity::setScale(float x, float y , float z)
{
	wmScale = scale(mat4(1.0f), vec3(x, y, z));
	this->updateWorld();
	return wmScale;
}

mat4x4 GameEntity::setRotation(float x, float y, float z)
{
	wmRot = rotate(mat4(1.0f),90.0f, vec3(x, y, z));
	this->updateWorld();
	return wmRot;
}

void GameEntity::updateWorld()
{
	worldMatrix = wmTrans * wmRot * wmScale;
}

GameEntity::GameEntity(IMesh* m, IRenderer* renderer)
{
	mesh = m;
	Renderer = renderer;
	localvertexShader = dynamic_cast<WinRenderer*>(Renderer)->getVertexShader();
	localpixelShader = dynamic_cast<WinRenderer*>(Renderer)->getPixelShader();
	this->setTranslation(0.0f, 0.0f, 0.0f);
	this->setScale(1.0f, 1.0f, 1.0f);
	this->setRotation(0.0f,0.0f,0.0f);
	updateWorld();

}

IMesh* GameEntity::getMesh()
{
	return mesh;
}

Material * GameEntity::getMaterial()
{
	return material;
}

void GameEntity::prepareMaterial()
{
	mat4x4 w, v, p;
	//w = Renderer->getworldMatrix();
	v = dynamic_cast<WinRenderer*>(Renderer)->getviewMatrix();
	p = dynamic_cast<WinRenderer*>(Renderer)->getprojectionMatrix();
	
	
	const float* world = (const float*)value_ptr(worldMatrix);
	const float* convertedView = (const float*)value_ptr(v);
	const float* convertedProjection = (const float*)value_ptr(p);
	localvertexShader->SetMatrix4x4("world", world);
	localvertexShader->SetMatrix4x4("view", convertedView);
	localvertexShader->SetMatrix4x4("projection", convertedProjection);
	localvertexShader->CopyAllBufferData();
	
	localvertexShader->SetShader();

	localpixelShader->SetShaderResourceView("wallTexture", this->getMaterial()->getSRV());
	localpixelShader->SetSamplerState("basicSampler", this->getMaterial()->getsamplerState());
	
	localpixelShader->CopyAllBufferData();
	localpixelShader->SetShader();

}

void GameEntity::LoadTextures()
{
	CreateWICTextureFromFile(dynamic_cast<WinRenderer*>(Renderer)->GetDevice(), dynamic_cast<WinRenderer*>(Renderer)->GetContext(), L"Knockdown_texture.JPG", 0, &SRV);
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
void GameEntity::InitializeMaterial()
{
	material = new Material(localvertexShader, localpixelShader, SRV, Sampler);

}
void  LightingInfo(DirectionalLight light)
{

}
GameEntity::~GameEntity()
{
}
