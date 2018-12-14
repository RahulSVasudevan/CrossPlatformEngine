
#include "Game.h"


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
//	bool done = false;
//
//	// loop until exit
//	while (!done) 
//	{
//		render->DrawQuad();
//	}
//
//	delete render;
//
//}