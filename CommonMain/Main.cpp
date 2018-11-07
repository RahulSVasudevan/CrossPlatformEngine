//#include "stdafx.h"

#include "Game.h"
#include "IRenderer.h"
#include "IMesh.h"

#ifdef _WIN32

#include <Windows.h>

#include "..\CrossPlatformEngine\WinRenderer.h"
#include "..\CrossPlatformEngine\WinRenderer.cpp"
#include "..\CrossPlatformEngine\WinMesh.h" 
#include "..\CrossPlatformEngine\WinMesh.cpp"
#include "..\CrossPlatformEngine\SimpleShader.h"
#include "..\CrossPlatformEngine\SimpleShader.cpp"



#endif


int main(int argc, const char *argv[])
{
	Game*game = new Game();
	game->Run();

	delete game;
	return(0);
}

//int main(int argc, const char *argv[])
//{
//
//	IRenderer *render = new PS4Renderer();
//
//	render->Init();
//
//	while (true) {
//		render->DrawQuad();
//	}
//
//	delete render;
//
//}