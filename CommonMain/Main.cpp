
#include "Game.h"
#include "IRenderer.h"
#include "IMesh.h"






#ifdef _WIN32


#include "..\CrossPlatformEngine\WinCanvas.h"
#include "..\CrossPlatformEngine\WinCanvas.cpp"
#include "..\CrossPlatformEngine\WinRenderer.h"
#include "..\CrossPlatformEngine\WinRenderer.cpp"
#include "..\CrossPlatformEngine\SimpleShader.h"
#include "..\CrossPlatformEngine\SimpleShader.cpp"
#include "..\CrossPlatformEngine\WinMesh.h" 
#include "..\CrossPlatformEngine\WinMesh.cpp"
#include <Windows.h>

#endif


int main()
{
	Game*game = new Game();
	game->Run();

	delete game;

	return(0);
}

