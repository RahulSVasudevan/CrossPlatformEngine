//#include "stdafx.h"
#include "Game.h"

#ifdef _WIN32
	#include "../CrossPlatformEngine/WinRenderer.h" 
    
#endif

Game::Game()
{
#ifdef _WIN32
	renderer = new WinRenderer();
	getInput = Keyboard::getInstance();
#endif
	
	renderer->Init();
}

Game::~Game() {
	//Necessary?
	//gameObjects.clear();
	//meshes.clear();

	delete renderer;
	delete getInput;
}

void Game::Init()
{
}

void Game::Draw()
{
	renderer->DrawQuad();

}

void Game::Run()
{
	while (renderer->MessageExist())
	{
		Draw();
		if (getInput->GetKeyDown('W'))
		{
			OutputDebugStringW(L"\nW was pressed");
		}
		renderer->EndFrame();
	}
}






