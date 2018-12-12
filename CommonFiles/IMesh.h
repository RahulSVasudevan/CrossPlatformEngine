#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <stdint.h>
#include "Maths.h"
#include"Lights.h"


using namespace glm;

struct VertexCommon
{
	vec3 Position;
	float pad1;
	
	vec4 Color;        
	
	vec3 Normal;
	float pad2;
	
	vec2 UV; 
	vec2 pad3;

	VertexCommon() { Position = vec3(0, 0, 0); Color = vec4(1, 1, 1, 1); Normal = vec3(0, 0, 0); UV = vec2(0, 0); pad1 = 0; pad2 = 0; pad3 = vec2(0, 0); };
	VertexCommon(vec3 pos, vec4 color, vec3 normal, vec2 uv) { Position = pos; Color = color; Normal = normal; UV = uv; pad1 = 0; pad2 = 0; pad3 = vec2(0, 0);}
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

	glm::mat4 world;
	VertexCommon * GetVertexData();
	uint16_t* GetIndexData();
	glm::mat4 GetWorldMatrix();

	void CheckInput(float x);
};

