#include "stdafx.h"
#include "WinMesh.h"


WinMesh::WinMesh(ID3D11Device* device) :IMesh()
{
	vertexBufferPointer = 0;
	indexBufferPointer = 0;

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.ByteWidth = sizeof(VertexCommon) * 3;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = vertexData;

	HRESULT hResult = device->CreateBuffer(&vbd, &initialVertexData, &vertexBufferPointer);


	//Index Buffer Creation

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = sizeof(uint16_t) * 3;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;


	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indexData;

	hResult = device->CreateBuffer(&ibd, &initialIndexData, &indexBufferPointer);
}

WinMesh::WinMesh(VertexCommon * vb, int vbSize, uint16_t * ib, int ibSize, ID3D11Device * device) :IMesh(vb,vbSize,ib,ibSize)
{
	InitializeBuffers(device);
}

WinMesh::WinMesh(const char * objFile, ID3D11Device * device):IMesh(objFile)
{
	InitializeBuffers(device);
}

WinMesh::~WinMesh()
{
	vertexBufferPointer->Release();
	indexBufferPointer->Release();
}

ID3D11Buffer * WinMesh::GetVertexBuffer()
{
	return vertexBufferPointer;
}

ID3D11Buffer * WinMesh::GetIndexBuffer()
{
	return indexBufferPointer;
}

void WinMesh::InitializeBuffers( ID3D11Device * device)
{
	vertexBufferPointer = 0;
	indexBufferPointer = 0;

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.ByteWidth = sizeof(VertexCommon) * vertexSize;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = vertexData;

	HRESULT hResult = device->CreateBuffer(&vbd, &initialVertexData, &vertexBufferPointer);


	//Index Buffer Creation

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = sizeof(uint16_t) * indexSize;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;


	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indexData;

	hResult = device->CreateBuffer(&ibd, &initialIndexData, &indexBufferPointer);

	int a = 0;
}
