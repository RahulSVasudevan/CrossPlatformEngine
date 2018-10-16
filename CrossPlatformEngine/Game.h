#pragma once

#include"Engine.h"
#include "GameObject.h"
#include "Mesh.h"

class Game: public Engine
{

public:
	Game();
	~Game();
	void Init();
	void Draw();

private:
	GameObject *gameObjects;
	Mesh *meshes;
};