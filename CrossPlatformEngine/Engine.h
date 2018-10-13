#pragma once

#include "IRenderer.h"

class Engine 
{

	IRenderer* renderer;

public:
	Engine();
	virtual void Init();
	virtual void Draw();
	void Run();
};