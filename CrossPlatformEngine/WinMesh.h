#pragma once


#include <d3d11.h>
#include "SimpleShader.h"
#include "..\CommonMain\IMesh.h"

#pragma comment(lib, "d3d11.lib")

using namespace DirectX;

class WinMesh: public IMesh 
{
	ID3D11Buffer * vertexBufferPointer;
	ID3D11Buffer * indexBufferPointer;

public: 

	WinMesh(ID3D11Device* device);
	WinMesh(VertexCommon* vb, int vbSize, unsigned int* ib, int ibSize, ID3D11Device* device);
	~WinMesh();
	ID3D11Buffer *GetVertexBuffer();
	ID3D11Buffer *GetIndexBuffer();

};