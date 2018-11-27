#pragma once
#include"SimpleShader.h"

class Material
{
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	ID3D11ShaderResourceView* SRV;
	ID3D11SamplerState* Sampler;
public:
	Material(SimpleVertexShader*, SimplePixelShader*, ID3D11ShaderResourceView*, ID3D11SamplerState*);
	SimpleVertexShader* getvertexShader();
	SimplePixelShader* getpixelShader();
	ID3D11ShaderResourceView* getSRV();
	ID3D11SamplerState* getsamplerState();
	~Material();
};
