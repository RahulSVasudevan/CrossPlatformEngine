
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
	wr = static_cast<WinRenderer*>(renderer);
	windowHandle = wr->GetWindowHandle();
#endif
	Init();
	
}

void Game::InitializeCanvas() {
#ifdef _WIN32
	canvas = new WinCanvas();
	wc = static_cast<WinCanvas*>(canvas);
#endif
}

void Game::PrepareCanvas() {
#ifdef _WIN32
	wc->AssignDeviceAndContext(wr->GetDevice(), wr->GetContext());
	wc->Initialize();
	wc->CreateTextureFromFile(L"../Assets/Textures/smiley.png", "smiley");
#endif
}

Game::~Game() {
	//Necessary?
	//gameObjects.clear();
	//meshes.clear();

	delete canvas;
	delete mesh;
	delete renderer;
}

void Game::Init()
{
	InitializeCanvas();
}

POINT GetMousePosition(HWND *hWnd) {
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(*hWnd, &pos);
	return pos;
}

void Game::Draw()
{
	renderer->DrawQuad();
	canvas->Render();
	//renderer->DrawMesh(mesh);
}

void Game::Run()
{
	while (renderer->MessageExist())
	{
		POINT mousePosition = GetMousePosition(windowHandle);
		canvas->Update(mousePosition.x, mousePosition.y);
		PrepareCanvas();
		Draw();

		renderer->EndFrame();
	}

}
