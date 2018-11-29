#pragma once
#include "../CommonFiles/Maths.h"
#include "Material.h"
#include"WinMesh.h"
#include"WinRenderer.h"
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
	WinRenderer* Renderer;
	SimpleVertexShader* localvertexShader;
	SimplePixelShader* localpixelShader;
	DirectionalLight Light;
	ID3D11ShaderResourceView* SRV;
	ID3D11SamplerState* Sampler;

public:
	mat4x4 worldMatrix;
	mat4x4 wmTrans;
	mat4x4 wmScale;
	mat4x4 wmRot;
	mat4x4 setTranslation(float, float, float);
	mat4x4 setScale(float, float, float);
	mat4x4 setRotation(float, float, float);
	void updateWorld();
	void LoadTextures();
	void InitializeMaterial();
	GameEntity(IMesh* m, Material* m1, WinRenderer* renderer);
	IMesh* getMesh();
	Material* getMaterial();
	void prepareMaterial();
	void  LightingInfo(DirectionalLight light);
	~GameEntity();
};