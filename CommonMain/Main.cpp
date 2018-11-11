
#include "Game.h"
#include "IRenderer.h"
#include "IMesh.h"

//#ifdef __clang__
//#include "..\PS4_Project2\PS4Renderer.h"
//#include "..\PS4_Project2\PS4Renderer.cpp"
//#include "..\PS4_Project2\ControllerInput.h"
//#include "..\PS4_Project2\ControllerInput.cpp"
//#include "..\PS4_Project2\sceFiles\embedded_shader.h"
//#include "..\PS4_Project2\sceFiles\embedded_shader.cpp"
//#include "..\PS4_Project2\sceFiles\stack_allocator.h"
//#include "..\PS4_Project2\sceFiles\stack_allocator.cpp"
//#include "..\PS4_Project2\sceFiles\memory_requests.h"
//#include "..\PS4_Project2\sceFiles\memory_requests.cpp"
//#endif 

//int main(int argc, const char *argv[])
//{
//	srand((unsigned)time(0));
//
//	uint32_t targetWidth = 1920;
//	uint32_t targetHeight = 1080;
//
//	PS4Renderer *render = new PS4Renderer();
//
//	render->Init();
//
//	bool done = false;
//
//	while (!done) {
//		//done = handleUserEvents();
//
//		//render->drawScene();
//		render->DrawQuad();
//	}
//
//	delete render;
//
//}



//
//#ifdef _WIN32
//
//
//#include "..\CrossPlatformEngine\WinRenderer.h"
//#include "..\CrossPlatformEngine\WinRenderer.cpp"
//#include "..\CrossPlatformEngine\SimpleShader.h"
//#include "..\CrossPlatformEngine\SimpleShader.cpp"
//#include "..\CrossPlatformEngine\WinMesh.h" 
//#include "..\CrossPlatformEngine\WinMesh.cpp"
//#include"..\CrossPlatformEngine\Keyboard.h"
//#include"..\CrossPlatformEngine\Keyboard.cpp"
//#include"..\CrossPlatformEngine\InputEvent.h"
//#include"..\CrossPlatformEngine\InputEvent.cpp"
//#include <Windows.h>
//
//#endif
//

int main()
{
	Game*game = new Game();
	game->Run();

	delete game;

	return(0);
}

