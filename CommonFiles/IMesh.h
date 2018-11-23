#pragma once

#include <stdint.h>

struct float3
{
	float x;
	float y;
	float z;

	float3() { x = 0;y = 0;z = 0; }
	float3( float a, float b, float c) {x = a;y = b;z = c; }
};

struct float4
{
	float r;
	float g;
	float b;
	float a;

	float4() { r = 0;g = 0;b = 0;a = 0; }
	float4(float w, float x, float y, float z) {r = w;g = x;b = y;a = z;}
}; 

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

