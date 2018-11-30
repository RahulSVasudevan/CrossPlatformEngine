
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

void Game::CreateCanvas() {
#ifdef _WIN32
	canvas = new WinCanvas();
	wc = static_cast<WinCanvas*>(canvas);
#endif
}

void Game::InitializeCanvas() {
#ifdef _WIN32
	wc->AssignDeviceAndContext(wr->GetDevice(), wr->GetContext());
	wc->Initialize();
	//wc->CreateTextureFromFile(L"../Assets/Textures/smiley.png", "smiley");
#endif
	//canvas->CreateTextureFromFile(L"../Assets/Textures/smiley.png", "smiley");
	canvas->LoadScene("../Assets/Scenes/Scene.txt");
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
	CreateCanvas();
}

#ifdef _WIN32
POINT GetMousePosition(HWND *hWnd) {
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(*hWnd, &pos);
	return pos;
}
#endif

void Game::Draw()
{
	renderer->DrawQuad();
	canvas->Render();
	//renderer->DrawMesh(mesh);
}

void Game::UpdateCanvas() {
	int x = 0;
	int y = 0;
#ifdef _WIN32
	POINT mousePosition = GetMousePosition(windowHandle);
	x = mousePosition.x;
	y = mousePosition.y;
#endif
	canvas->Update(x, y);
	//PrepareCanvas();
}

void Game::Run()
{
	//Wait for the device and context to be created, then prepare the canvas
	while (!canvas->IsReady()) {
		InitializeCanvas();
	}
	while (renderer->MessageExist())
	{
		UpdateCanvas();
		Draw();

		renderer->EndFrame();
	}

}
