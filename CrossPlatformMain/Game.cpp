
#include "Game.h"



#ifdef _WIN32
	#include "..\WindowsLibrary\WinRenderer.h"
	#include "..\WindowsLibrary\WinMesh.h"
#elif __clang__
	#include "..\PS4Library\PS4Renderer.h"
#endif




Game::Game()
{
	// Temp Mesh Data
	VertexData = new VertexCommon[4];
	*VertexData = VertexCommon(vec3(+0.0f, +1.0f, +0.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f));
	*(VertexData + 1) = VertexCommon(vec3(-1.0f, +1.0f, +0.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f));
	*(VertexData + 2) = VertexCommon(vec3(+0.0f, -1.0f, +0.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f));
	*(VertexData + 3) = VertexCommon(vec3(-1.0f, -1.0f, +0.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f));

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


	light.DirLightColor = vec4(1, 0, 0, 1.0f);
	light.AmbientColor = vec4(0.9, 0.9, 0, 1.0f);
	light.DirLightDirection = vec3(0, 10, 0);
	

#ifdef _WIN32
	renderer = new WinRenderer();
	getInput = Keyboard::getInstance();
	renderer->Init();
	//mesh = new WinMesh(VertexData, 4, IndexData, 6, dynamic_cast<WinRenderer*>(renderer)->GetDevice());
	//mesh2 = new WinMesh(VertexData2, 4, IndexData, 6, dynamic_cast<WinRenderer*>(renderer)->GetDevice());
	
	mesh2 = new WinMesh("../CommonFiles/Lamborghini_Aventador.obj", dynamic_cast<WinRenderer*>(renderer)->GetDevice());
	Entity = new  GameEntity(mesh2, renderer);
	Entity->LoadTextures();
	Entity->InitializeMaterial();
	renderer->LightingInfo(light);
#elif __clang__
	renderer = new PS4Renderer();
	getInput = ControllerInput::getInstance();
	getInput->initialize();
	renderer->Init();
	
	//mesh = new PS4Mesh(VertexData, 4, IndexData, 6, dynamic_cast<PS4Renderer*>(renderer)->GetStackAllocater());
	//mesh2 = new PS4Mesh(VertexData2, 4, IndexData2, 6, dynamic_cast<PS4Renderer*>(renderer)->GetStackAllocater());

	mesh2 = new PS4Mesh("/app0/sphere.obj", dynamic_cast<PS4Renderer*>(renderer)->GetStackAllocater());


#endif 


	

}



Game::~Game() {

	//delete mesh;
	delete mesh2;
	delete Entity;
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
	getInput->update();
	Entity->prepareMaterial();
	renderer->DrawMesh(mesh2);
}

void Game::Run()
{
	while (renderer->MessageExist())
	{
		renderer->BeginFrame();
		
		Draw();


		
		if (getInput->GetKeyDown('W') || getInput->isButtonDown(Button::BUTTON_SQUARE))
		{
			printf("## square\n");
			//mesh2->CheckInput(1.0f);
		}
		if (getInput->isButtonDown(Button::BUTTON_CIRCLE) || getInput->GetKeyDown('V'))
		{
			printf("## CIRCLE \n");
			//mesh2->CheckInput(2.0f);
		}
		renderer->EndFrame();
	}

}
