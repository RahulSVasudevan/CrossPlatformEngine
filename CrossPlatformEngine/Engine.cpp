#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
	renderer = renderer->NewPlatformRenderer();
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

		renderer->EndFrame();
	}
	
}
