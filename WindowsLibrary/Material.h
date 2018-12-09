#pragma once
#include"../CommonFiles/IRenderer.h"
#include"../WindowsLibrary/WinRenderer.h"
#include"SimpleShader.h"
#include"WinMesh.h"
#include <DirectXMath.h>
#include"WICTextureLoader.h"




class Material
{
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	ID3D11ShaderResourceView* SRV;
	ID3D11SamplerState* Sampler;
	IRenderer* Renderer;
public:
	Material(SimpleVertexShader*, SimplePixelShader*, IRenderer*);
	SimpleVertexShader* getvertexShader();
	SimplePixelShader* getpixelShader();
	ID3D11ShaderResourceView* getSRV();
	ID3D11SamplerState* getsamplerState();
	void LoadTextures();
	void DatatoShader();
	~Material();
};
