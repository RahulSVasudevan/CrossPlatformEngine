#pragma once

#include "IRenderer.h"

class Engine 
{
protected:
	

public:
	Engine();
	~Engine();
	virtual void Init();
	virtual void Draw();
	void Run();
};