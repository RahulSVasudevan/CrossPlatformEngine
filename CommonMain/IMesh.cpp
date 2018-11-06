#include "IMesh.h"

IMesh::IMesh()
{
	vertexData[0].Position = float3(+1.0f, +1.0f, +0.0f);
	vertexData[0].Color = float4(1.0f, 0.0f, 0.0f, 1.0f);
	
	vertexData[1].Position = float3(-1.0f, +1.0f, +0.0f);
	vertexData[1].Color = float4(1.0f, 0.0f, 0.0f, 1.0f);

	vertexData[2].Position = float3(+1.0f, -1.0f, +0.0f);
	vertexData[2].Color = float4(1.0f, 0.0f, 0.0f, 1.0f);

	indexData[0] = 0;
	indexData[1] = 2;
	indexData[2] = 1;

}
