#pragma once

#include "..\CommonFiles\IRenderer.h"
#include "..\CommonFiles\Lights.h"
#include"..\CommonFiles\Input.h"
#include"..\CommonFiles\IEntity.h"
#include"..\CommonFiles\IMaterial.h"
#include"..\CommonFiles\Parser.h"
#include"..\CommonFiles\SceneObjectData.h"
#include "..\CommonFiles\IAudio.h"
#include "..\CommonFiles\ICanvas.h"
#include <fstream>
#include <map>
#include <string>
//#include <unordered_map>


using namespace std;

class Game
{
	IMesh *mesh;
	IEntity *entity;
	IRenderer * renderer;
	ICanvas *canvas;
	IAudio * audioRenderer;

	Input* getInput;

	IMesh * skyMesh;
	IEntity* sky;

	IMaterial* Mat;

	IMesh * FloorMesh;
	IMaterial*  FloorMat;
	IEntity* Floor;

	IMesh *planeMesh;
	IMaterial *planeMaterial;
	IEntity *planeEntity;

	VertexCommon * skyVertexData;
	uint16_t * skyIndexData;
	
	
	VertexCommon * VertexData;
	uint16_t * IndexData;

	DirectionalLight light;

	map<string, IEntity*> entities;
	map<string, IMesh*> meshes;
	enum Button
	{
		BUTTON_L3 = 0x00000002,
		BUTTON_R3 = 0x00000004,
		BUTTON_OPTIONS = 0x00000008,
		BUTTON_UP = 0x00000010,
		BUTTON_RIGHT = 0x00000020,
		BUTTON_DOWN = 0x00000040,
		BUTTON_LEFT = 0x00000080,
		BUTTON_L2 = 0x00000100,
		BUTTON_R2 = 0x00000200,
		BUTTON_L1 = 0x00000400,
		BUTTON_R1 = 0x00000800,
		BUTTON_TRIANGLE = 0x00001000,
		BUTTON_CIRCLE = 0x00002000,
		BUTTON_CROSS = 0x00004000,
		BUTTON_SQUARE = 0x00008000,
		BUTTON_TOUCH_PAD = 0x00100000,
		BUTTON_INTERCEPTED = 0x80000000,
	};

	bool upPressed;
	bool downPressed;
	bool confirmPressed;
	//DirectionalLight light1;

public:
	Game();
	~Game();
	void Init();
	void Draw();
	void UpdateCanvas();
	void Run();

	void InitializeCanvas();

	void CreateMeshFromFile(string meshName, string path);

	//Create an entity and assign a mesh
	void CreateEntity(string entityName, string meshName);
	void DestroyEntity(string entityName);

	void UnloadScene();
	void LoadScene(string filename);
};