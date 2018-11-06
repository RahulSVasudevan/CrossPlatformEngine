#include "WinMesh.h"
#include "..\CommonMain\IMesh.h"

WinMesh::WinMesh(ID3D11Device* device) :IMesh()
{
	vertexBufferPointer = 0;
	indexBufferPointer = 0;

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.ByteWidth = sizeof(Vertex) * 3;
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
	ibd.ByteWidth = sizeof(unsigned int) * 3;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;


	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indexData;

	hResult = device->CreateBuffer(&ibd, &initialIndexData, &indexBufferPointer);
}

ID3D11Buffer * WinMesh::GetVertexBuffer()
{
	return vertexBufferPointer;
}

ID3D11Buffer * WinMesh::GetIndexBuffer()
{
	return indexBufferPointer;
}
