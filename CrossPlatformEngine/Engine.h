#pragma once

#include "IRenderer.h"
#include "Keyboard.h"
#include<Windows.h>
#include"InputEvent.h"
#include "WinRenderer.h"
class Engine 
{
protected:
	WinRenderer* renderer;
public:
	Engine();
	virtual void Init();
	virtual void Draw();
	void Run();
};