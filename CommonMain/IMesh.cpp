
#include "IMesh.h"

IMesh::IMesh()
{
	vertexData = new VertexCommon[3];
	*vertexData = VertexCommon(float3(+1.0f, +1.0f, +0.0f), float4(1.0f, 0.0f, 0.0f, 1.0f));
	*(vertexData + 1) = VertexCommon(float3(-1.0f, +1.0f, +0.0f), float4(1.0f, 0.0f, 0.0f, 1.0f));
	*(vertexData + 2) = VertexCommon(float3(+1.0f, -1.0f, +0.0f), float4(1.0f, 0.0f, 0.0f, 1.0f));

	indexData = new unsigned int[3];
	*indexData = 0;
	*(indexData + 1) = 2;
	*(indexData + 2) = 1;

}

IMesh::IMesh(VertexCommon* vb, unsigned int* ib)
{
	vertexData = vb;
	indexData = ib;
}

IMesh::~IMesh()
{
	delete[] vertexData;
	delete[] indexData;
}


