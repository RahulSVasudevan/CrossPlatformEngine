#pragma once

#include "..\CommonFiles\IRenderer.h"
#include "..\CommonFiles\Lights.h"
#include"..\CommonFiles\Input.h"
#include"..\WindowsLibrary\GameEntity.h"
#include "..\CommonFiles\IAudio.h"
//#include <unordered_map>


using namespace std;

class Game
{

	IRenderer * renderer;

	IMesh * mesh;
	IMesh * mesh2;
	IAudio * audioRenderer;
	Input* getInput;
	GameEntity* Entity;
	VertexCommon * VertexData;
	VertexCommon * VertexData2;
	uint16_t * IndexData;
	uint16_t * IndexData2;
	DirectionalLight light;
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
	DirectionalLight light1;

public:
	Game();
	~Game();
	void Init();
	void Draw();
	void Run();


};