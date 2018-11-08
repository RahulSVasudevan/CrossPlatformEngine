
#include "Game.h"

#ifdef _WIN32
	#include "../CrossPlatformEngine/WinRenderer.h" 
	#include "../CrossPlatformEngine/WinMesh.h" 
#endif

Game::Game()
{
	VertexData = new VertexCommon[3];
	*VertexData = VertexCommon(float3(+1.0f, +1.0f, +0.0f), float4(1.0f, 1.0f, 0.0f, 1.0f));
	*(VertexData + 1) = VertexCommon(float3(-1.0f, +1.0f, +0.0f), float4(1.0f, 1.0f, 0.0f, 1.0f));
	*(VertexData + 2) = VertexCommon(float3(+1.0f, -1.0f, +0.0f), float4(1.0f, 1.0f, 0.0f, 1.0f));

	IndexData = new unsigned int[3];
	*IndexData = 0;
	*(IndexData + 1) = 2;
	*(IndexData + 2) = 1;

#ifdef _WIN32
	renderer = new WinRenderer();
	renderer->Init();
	mesh = new WinMesh(VertexData, 3, IndexData, 3, dynamic_cast<WinRenderer*>(renderer)->GetDevice());
#endif

	
}

Game::~Game() {
	//Necessary?
	//gameObjects.clear();
	//meshes.clear();

	delete mesh;
	delete renderer;
}

void Game::Init()
{
}

void Game::Draw()
{
	renderer->DrawQuad();
	//renderer->DrawMesh(mesh);
}

void Game::Run()
{
	while (renderer->MessageExist())
	{
		Draw();

		renderer->EndFrame();
	}

}
