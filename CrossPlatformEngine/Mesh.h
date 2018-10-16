#pragma once

struct Mesh {
	int *Vertices;
	int *Indices;
	int VertexCount;
	int IndexCount;
	int PixelShaderID;
	int VertexShaderID;
};