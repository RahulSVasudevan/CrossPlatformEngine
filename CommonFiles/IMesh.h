#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <stdint.h>
#include "Maths.h"
#include "Lights.h"

using namespace glm;

struct VertexCommon
{
	vec3 Position;	    // The position of the vertex
	vec4 Color;        // The color of the vertex
	vec3 Normal;
	vec2 UV;

	VertexCommon() { Color = vec4(1, 1, 1, 1); };
	VertexCommon(vec3 a, vec4 b, vec3 c) { Position = a; Color = b; Normal = c; }
};


class IMesh 
{
protected:
	VertexCommon * vertexData;
	uint16_t* indexData;

	
	std::vector<VertexCommon> verts;           // Verts we're assembling
	std::vector<uint16_t> indices;           // Indices of these verts
	std::vector<vec3> normals;
	std::vector<vec2> uvs;           // UVs from the file


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

