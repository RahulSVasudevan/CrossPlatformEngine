
#include "IMesh.h"

IMesh::IMesh()
{
	vertexSize = 0;
	indexSize = 0;
}

IMesh::IMesh(VertexCommon* vb, uint16_t* ib)
{
	vertexData = vb;
	indexData = ib;
}

IMesh::~IMesh()
{
	
}

VertexCommon * IMesh::GetVertexData()
{
	return vertexData;
}

uint16_t * IMesh::GetIndexData()
{
	return indexData;
}


