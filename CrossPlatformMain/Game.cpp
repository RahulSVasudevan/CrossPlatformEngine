
#include "Game.h"



#ifdef _WIN32
	#include "..\WindowsLibrary\WinRenderer.h"
#include "..\WindowsLibrary\WinMesh.h"
#endif




Game::Game()
{
	// Temp Mesh Data
	VertexData = new VertexCommon[4];
	*VertexData = VertexCommon(vec3(+0.0f, +1.0f, +0.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
	*(VertexData + 1) = VertexCommon(vec3(-1.0f, +1.0f, +0.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
	*(VertexData + 2) = VertexCommon(vec3(+0.0f, -1.0f, +0.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
	*(VertexData + 3) = VertexCommon(vec3(-1.0f, -1.0f, +0.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));

	VertexData2 = new VertexCommon[4];
	*VertexData2 = VertexCommon(vec3(+1.0f, +1.0f, +0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	*(VertexData2 + 1) = VertexCommon(vec3(0.0f, +1.0f, +0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	*(VertexData2 + 2) = VertexCommon(vec3(+1.0f, -1.0f, +0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	*(VertexData2 + 3) = VertexCommon(vec3(0.0f, -1.0f, +0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));

	IndexData = new uint16_t[6];
	*IndexData = 0;
	*(IndexData + 1) = 1;
	*(IndexData + 2) = 2;
	*(IndexData + 3) = 1;
	*(IndexData + 4) = 2;
	*(IndexData + 5) = 3;

	IndexData2 = new uint16_t[6];
	*IndexData2 = 0;
	*(IndexData2 + 1) = 1;
	*(IndexData2 + 2) = 2;
	*(IndexData2 + 3) = 1;
	*(IndexData2 + 4) = 2;
	*(IndexData2 + 5) = 3;


#ifdef _WIN32
	renderer = new WinRenderer();
	renderer->Init();
	//mesh = new WinMesh(VertexData, 4, IndexData, 6, dynamic_cast<WinRenderer*>(renderer)->GetDevice());
	//mesh2 = new WinMesh(VertexData2, 4, IndexData, 6, dynamic_cast<WinRenderer*>(renderer)->GetDevice());
	
	mesh2 = new WinMesh("../CommonFiles/sphere.obj", dynamic_cast<WinRenderer*>(renderer)->GetDevice());
#endif 
		

	light1.AmbientColor = vec4(0.1f, 0.1f, 0.1f, 0.1f);
	light1.DiffuseColor = vec4(0, 0, 1, 1);
	light1.Direction = vec3(1, -1, 0);

}



Game::~Game() {

	//delete mesh;
	delete mesh2;

	delete[] VertexData;
	delete[] VertexData2;
	delete[] IndexData;
	delete[] IndexData2;

	delete renderer;
}

void Game::Init()
{
	
}

void Game::Draw()
{
	//renderer->DrawQuad();

	//renderer->DrawMesh(mesh);

	renderer->DrawMesh(mesh2);
}

void Game::Run()
{
	while (renderer->MessageExist())
	{
		renderer->BeginFrame();

		Draw();

		renderer->EndFrame();
	}

}
