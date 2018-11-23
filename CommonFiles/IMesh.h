#pragma once

#include <stdint.h>
#include "Maths.h"


struct VertexCommon
{
	float3 Position;	    // The position of the vertex
	float4 Color;        // The color of the vertex

	VertexCommon() {};
	VertexCommon(float3 a, float4 b) { Position = a; Color = b;}
};


class IMesh 
{
protected:
	VertexCommon * vertexData;
	uint16_t* indexData;


public:

	IMesh();
	IMesh(VertexCommon* vb, uint16_t* ib);
	virtual ~IMesh();
	
	int vertexSize;
	int indexSize;
	
	VertexCommon * GetVertexData();
	uint16_t* GetIndexData();
};

