//#include "stdafx.h"
#include "Game.h"

#ifdef _WIN32
	#include "../CrossPlatformEngine/WinRenderer.h" 
    #include"../CrossPlatformEngine/Keyboard.h"
#endif

Game::Game()
{
#ifdef _WIN32
	renderer = new WinRenderer();
#endif
	
	renderer->Init();
}

Game::~Game() {
	//Necessary?
	//gameObjects.clear();
	//meshes.clear();

	delete renderer;
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
		if (Keyboard::getInstance()->KeyIsPressed('W'))
		{
			OutputDebugStringW(L"\nW was pressed");
		}
		renderer->EndFrame();
	}
}


