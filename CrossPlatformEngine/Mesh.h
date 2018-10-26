#pragma once

#include <map>
using namespace std;

struct Mesh {
	//May not need to be ordered maps
	map<int, Vector3> Vertices;
	map<int, int> Indices;
	//int VertexCount;
	//int IndexCount;
	int PixelShaderID;
	int VertexShaderID;
};