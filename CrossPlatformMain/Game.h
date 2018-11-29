#pragma once

#include "..\CommonFiles\IRenderer.h"
#include "..\CommonFiles\Lights.h"
#include"..\WindowsLibrary\GameEntity.h"

//#include <unordered_map>


using namespace std;

class Game
{

	IRenderer * renderer;

	IMesh * mesh;
	IMesh * mesh2;
	GameEntity* Entity;
	Material* TestMaterial;
	VertexCommon * VertexData;
	VertexCommon * VertexData2;
	uint16_t * IndexData;
	uint16_t * IndexData2;

	DirectionalLight light;

public:
	Game();
	~Game();
	void Init();
	void Draw();
	void Run();


};