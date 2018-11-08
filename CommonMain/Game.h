#pragma once

#include "IRenderer.h"
#include <unordered_map>

#ifdef _WIN32
	#include "../CrossPlatformEngine/WinCanvas.h"
#include "../CrossPlatformEngine/WinRenderer.h"
#endif

using namespace std;

class Game
{
	IRenderer* renderer;
	IMesh * mesh;

	VertexCommon * VertexData;
	unsigned int * IndexData;

public:
	Game();
	~Game();
	void Init();
	void Draw();
	void Run();

private:
	//unordered_map<int, GameObject> gameObjects;
	//unordered_map<int, Mesh> meshes;
	//GameObject *gameObjects;
	//Mesh *meshes;
	void InitializeCanvas();
	void PrepareCanvas();
	ICanvas *canvas;
#ifdef _WIN32
	WinRenderer *wr;
	WinCanvas *wc;
#endif
};