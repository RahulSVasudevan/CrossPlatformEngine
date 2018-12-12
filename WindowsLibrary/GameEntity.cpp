
#include "GameEntity.h"
//#include <WICTextureLoader.h>

using namespace DirectX;

void GameEntity::setTranslation(float x, float y, float z)
{
	//wmTrans += vec3(x, y, z);
	wmTrans += forward;
	this->updateWorld();
	
}

void GameEntity::setScale(float x, float y , float z)
{
	wmScale = vec3(x, y, z);
	this->updateWorld();
}

void GameEntity::setRotation(float angle)
{
	wmRot += angle;
	forward = vec3(sin(wmRot), 0, cos(wmRot));
	this->updateWorld();
}

void GameEntity::moveForward(float speed)
{
	wmTrans += forward * speed;
	this->updateWorld();
}

WinMesh* GameEntity::GetMesh()
{
	return (WinMesh*)mesh;
}

void GameEntity::updateWorld()
{


	worldMatrix = glm::translate(mat4(1.0f), wmTrans);
	worldMatrix = glm::rotate(worldMatrix, wmRot, vec3(0,1,0));
	worldMatrix = glm::scale(worldMatrix, wmScale);
	

	worldMatrix = glm::transpose(worldMatrix);

}

mat4x4 GameEntity::GetWorldMatrix()
{
	return worldMatrix;
}

GameEntity::GameEntity(IMesh* m, IMaterial* mat)
{
	mesh = m;
	material = mat;
	//Renderer = renderer;
	/*localvertexShader = dynamic_cast<WinRenderer*>(Renderer)->getVertexShader();
	localpixelShader = dynamic_cast<WinRenderer*>(Renderer)->getPixelShader();*/
	wmTrans = glm::vec3(0.0f, 0.0f, 0.0f);
	wmScale = glm::vec3(1.0f, 1.0f, 1.0f);
	wmRot = 0;
	forward = vec3(0, 0, -1);
	//position = vec4(0.0f, 0.0f, 0.0f,1.0f);
	updateWorld();
}

//IMesh* GameEntity::getMesh()
//{
//	return mesh;
//}
//
//Material * GameEntity::getMaterial()
//{
//	return material;
//}

//void GameEntity::prepareMaterial()
//{
//	mat4x4 w, v, p;
//	//w = Renderer->getworldMatrix();
//	v = dynamic_cast<WinRenderer*>(Renderer)->getviewMatrix();
//	p = dynamic_cast<WinRenderer*>(Renderer)->getprojectionMatrix();
//	
//	//const float* world = (const float*)value_ptr(worldMatrix);
//	const float* world = (const float*)value_ptr(glm::mat4(1.0f));
//	const float* convertedView = (const float*)value_ptr(v);
//	const float* convertedProjection = (const float*)value_ptr(p);
//	localvertexShader->SetMatrix4x4("world", world);
//	localvertexShader->SetMatrix4x4("view", convertedView);
//	localvertexShader->SetMatrix4x4("projection", convertedProjection);
//	localvertexShader->CopyAllBufferData();
//	localvertexShader->SetShader();
//
//	localpixelShader->SetShaderResourceView("wallTexture", this->getMaterial()->getSRV());
//	localpixelShader->SetSamplerState("basicSampler", this->getMaterial()->getsamplerState());
//	
//	localpixelShader->CopyAllBufferData();
//	localpixelShader->SetShader();
//}

//void GameEntity::LoadTextures()
//{
//	CreateWICTextureFromFile(dynamic_cast<WinRenderer*>(Renderer)->GetDevice(), dynamic_cast<WinRenderer*>(Renderer)->GetContext(), L"../CommonFiles/Lamborginhi_Aventador_diffuse.jpeg", 0, &SRV);
//	D3D11_SAMPLER_DESC sd = {}; // Zeros it out
//	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
//	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
//	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
//	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // Tri-linear filtering
//												 //sd.Filter = D3D11_FILTER_ANISOTROPIC;
//												 //sd.MaxAnisotropy = 16;
//	sd.MaxLOD = D3D11_FLOAT32_MAX;
//
//	dynamic_cast<WinRenderer*>(Renderer)->GetDevice()->CreateSamplerState(&sd, &Sampler);
//}
//void GameEntity::InitializeMaterial()
//{
//	material = new Material(localvertexShader, localpixelShader,Renderer);
//
//}
void  LightingInfo(DirectionalLight light)
{

}
GameEntity::~GameEntity()
{
	//delete material;
	
}
