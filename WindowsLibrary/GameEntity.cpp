#include "GameEntity.h"

GameEntity::GameEntity(SimpleVertexShader* vShader, SimplePixelShader* pShader, ID3D11ShaderResourceView* srv, ID3D11SamplerState* sampler)
{
	vertexShader = vShader;
	pixelShader = pShader;
	SRV = srv;
	Sampler = sampler;
}

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

GameEntity::GameEntity(IMesh* m, Material* m1)
{
	mesh = m;
	material = m1;
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

void GameEntity::prepareMaterial(mat4x4 w, mat4x4 v, mat4x4 p)
{

	SimpleVertexShader* localvertexShader = this->getMaterial()->getvertexShader();
	SimplePixelShader* localpixelShader = this->getMaterial()->getpixelShader();
	
	const float* world = (const float*)value_ptr(worldMatrix);
	const float* convertedView = (const float*)value_ptr(v);
	const float* convertedProjection = (const float*)value_ptr(p);
	localvertexShader->SetMatrix4x4("world", world);
	localvertexShader->SetMatrix4x4("view", convertedView);
	localvertexShader->SetMatrix4x4("projection", convertedProjection);
	localvertexShader->CopyAllBufferData();
	localpixelShader->CopyAllBufferData();
	localvertexShader->SetShader();

	localpixelShader->SetShaderResourceView("wallTexture", this->getMaterial()->getSRV());
	localpixelShader->SetSamplerState("basicSampler", this->getMaterial()->getsamplerState());
	localpixelShader->SetShader();

}

GameEntity::~GameEntity()
{
}
