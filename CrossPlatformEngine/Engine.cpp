#include "stdafx.h"
#include "Engine.h"
#include<iostream>

Engine::Engine()
{
	renderer = static_cast<WinRenderer*>(renderer->NewPlatformRenderer());
	renderer->Init();
}

void Engine::Init()
{
}

void Engine::Draw()
{
}

void Engine::Run()
{
	//renderer->MessageLoop();

	while (renderer->MessageExist())
	{		
		Draw();
		if (Keyboard::getInstance()->KeyIsPressed('W'))
		{
			OutputDebugStringW(L"\nW was pressed");
		}
		while (!Keyboard::getInstance()->KeyBufferIsEmpty())
		{
			InputEvent iEvent = Keyboard::getInstance()->ReadKey();
			unsigned char keycode = iEvent.getKey();
		}
		//while (!Keyboard::getInstance()->CharBufferIsEmpty())
		//{
		//	//std::cout << "char buffer is not empty" << std::endl;
		//}
		renderer->EndFrame();						
	}

	
}
