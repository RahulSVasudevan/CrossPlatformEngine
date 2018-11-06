//#include "stdafx.h"

#include "Game.h"
#include "IRenderer.h"






#ifdef _WIN32


#include "..\CrossPlatformEngine\WinRenderer.h"
#include "..\CrossPlatformEngine\WinRenderer.cpp"
#include "..\CrossPlatformEngine\SimpleShader.h"
#include "..\CrossPlatformEngine\SimpleShader.cpp"
#include"..\CrossPlatformEngine\Keyboard.h"
#include"..\CrossPlatformEngine\Keyboard.cpp"
#include"..\CrossPlatformEngine\InputEvent.h"
#include"..\CrossPlatformEngine\InputEvent.cpp"
#include <Windows.h>

#endif


int main(int argc, const char *argv[])
{
	Game*game = new Game();
	game->Run();

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