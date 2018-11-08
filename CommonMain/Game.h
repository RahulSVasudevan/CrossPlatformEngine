#pragma once


//#include "GameObject.h"
//#include "Mesh.h"
#include "IRenderer.h"
#include"Input.h"
#include <unordered_map>


using namespace std;

class Game
{
	IRenderer* renderer;
	Input *getInput;
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
};