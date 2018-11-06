#pragma once

struct float3
{
	float a;
	float b;
	float c;

	float3( float x, float y, float z) {x = a;y = b;z = c; }
};

struct float4
{
	float a;
	float b;
	float c;
	float d;

	float4(float w, float x, float y, float z) {w = a;x = b;y = c;z = d;}
}; 

struct Vertex
{
	float3 Position;	    // The position of the vertex
	float4 Color;        // The color of the vertex
};


class IMesh 
{
protected:
	Vertex* vertexData;
	unsigned int* indexData;

public:

	IMesh();
};