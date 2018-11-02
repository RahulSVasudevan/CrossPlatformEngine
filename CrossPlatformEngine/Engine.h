#pragma once

#include "IRenderer.h"

class Engine 
{
protected:
	IRenderer* renderer;

public:
	Engine();
	~Engine();
	virtual void Init();
	virtual void Draw();
	void Run();
};