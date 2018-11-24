#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <stdint.h>
#include "Maths.h"


struct VertexCommon
{
	float3 Position;	    // The position of the vertex
	float4 Color;        // The color of the vertex
	float3 Normal;
	float2 UV;

	VertexCommon() { Color = float4(1, 1, 1, 1); };
	VertexCommon(float3 a, float4 b) { Position = a; Color = b;}
};


class IMesh 
{
protected:
	VertexCommon * vertexData;
	uint16_t* indexData;

	
	std::vector<VertexCommon> verts;           // Verts we're assembling
	std::vector<uint16_t> indices;           // Indices of these verts

public:

	IMesh();
	IMesh(VertexCommon* vb,int vbSize, uint16_t* ib,int ibSize);
	IMesh(const char*objFile);
	virtual ~IMesh();
	
	int vertexSize;
	int indexSize;
	
	VertexCommon * GetVertexData();
	uint16_t* GetIndexData();
};

