#pragma once

#include"Engine.h"
#include "GameObject.h"
#include "Mesh.h"
#include <unordered_map>

using namespace std;

class Game: public Engine
{

public:
	Game();
	~Game();
	void Init();
	void Draw();

private:
	unordered_map<int, GameObject> gameObjects;
	unordered_map<int, Mesh> meshes;
	//GameObject *gameObjects;
	//Mesh *meshes;
};