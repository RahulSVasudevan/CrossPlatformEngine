#pragma once
#include"../CommonFiles/IEntity.h"
#include"../CommonFiles/IMaterial.h"
#include "../CommonFiles/Maths.h"
#include "Material.h"
#include"WinMesh.h"
#include"../WindowsLibrary/WinRenderer.h"
#include"../CommonFiles/IRenderer.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
//#include "WICTextureLoader.h"

using namespace glm;
class GameEntity	: public IEntity
{	vec4 position;
	vec3 rotation;
	vec3 scaleValue;
	IMesh* mesh;
	IMaterial* material;
	IRenderer* Renderer;
	SimpleVertexShader* localvertexShader;
	SimplePixelShader* localpixelShader;
	/*DirectionalLight Light;*/
	ID3D11ShaderResourceView* SRV;
	ID3D11SamplerState* Sampler;

public:
	GameEntity(IMesh* m, IMaterial* mat);
	mat4x4 worldMatrix;
	vec3 wmTrans;
	vec3 wmScale;
	vec3 wmRot;
	void setTranslation(float, float, float);
	void setScale(float, float, float);
	void setRotation(float, float, float);
	void updateWorld();
	//void LoadTextures();
	//void InitializeMaterial();
	//IMesh* getMesh();
	//Material* getMaterial();
	//void prepareMaterial();
	//void  LightingInfo(DirectionalLight light);
	~GameEntity();
};