#pragma once
#include "../CommonFiles/Maths.h"
#include "Material.h"
#include"WinMesh.h"
#include"../WindowsLibrary/WinRenderer.h"
#include"../CommonFiles/IRenderer.h"
#include "SimpleShader.h"
#include <DirectXMath.h>

using namespace glm;
class GameEntity
{	vec3 position;
	vec3 rotation;
	vec3 scaleValue;
	IMesh* mesh;
	Material* material;
	IRenderer* Renderer;
	SimpleVertexShader* localvertexShader;
	SimplePixelShader* localpixelShader;
	/*DirectionalLight Light;*/
	ID3D11ShaderResourceView* SRV;
	ID3D11SamplerState* Sampler;

public:
	GameEntity(IMesh* m, IRenderer* renderer);
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
	IMesh* getMesh();
	Material* getMaterial();
	void prepareMaterial();
	//void  LightingInfo(DirectionalLight light);
	~GameEntity();
};