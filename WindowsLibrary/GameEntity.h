#pragma once
#include "../CommonFiles/Maths.h"
#include "Material.h"
#include"WinMesh.h"
#include "SimpleShader.h"
#include <DirectXMath.h>

using namespace glm;
class GameEntity
{

	vec3 position;
	vec3 rotation;
	vec3 scaleValue;
	IMesh* mesh;
	Material* material;
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	ID3D11ShaderResourceView* SRV;
	ID3D11SamplerState* Sampler;

public:
	mat4x4 worldMatrix;
	mat4x4 wmTrans;
	mat4x4 wmScale;
	mat4x4 wmRot;
	GameEntity(SimpleVertexShader* vShader, SimplePixelShader* pShader, ID3D11ShaderResourceView* srv, ID3D11SamplerState* sampler);
	mat4x4 setTranslation(float, float, float);
	mat4x4 setScale(float, float, float);
	mat4x4 setRotation(float, float, float);
	void updateWorld();
	GameEntity(IMesh* m, Material* m1);
	IMesh* getMesh();
	Material* getMaterial();
	void prepareMaterial(mat4x4, mat4x4, mat4x4 );
	~GameEntity();
};