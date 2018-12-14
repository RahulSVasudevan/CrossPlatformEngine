#ifdef _WIN32
#define ASSETS "../CrossPlatformMain/UIScenes/"
#else
#define ASSETS "/app0/UIScenes/"
#endif

#include "Game.h"



#ifdef _WIN32
#include "..\WindowsLibrary\WinRenderer.h"
#include "..\WindowsLibrary\WinCanvas.h"
#include "..\WindowsLibrary\WinMesh.h"
#include"..\WindowsLibrary\GameEntity.h"
#include "..\WindowsLibrary\WinAudio.h"
#elif __clang__
#include "..\PS4Library\PS4Renderer.h"
#include "..\PS4Library\PS4Canvas.h"
#endif

#define audioSound				((char*)"../Assets/Sounds/RollingSpace.wav")


Game::Game()
{
	// Temp Mesh Data
	VertexData = new VertexCommon[4];
	*VertexData = VertexCommon(vec3(+1000.0f, 0.0f, +1000.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f), vec3(0, 1, 0), vec2(1, 1));
	*(VertexData + 1) = VertexCommon(vec3(-1000.0f, 0.0f, +1000.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f), vec3(0, 1, 0), vec2(0, 1));
	*(VertexData + 2) = VertexCommon(vec3(+1000.0f, 0.0f, -1000.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f), vec3(0, 1, 0), vec2(1, 0));
	*(VertexData + 3) = VertexCommon(vec3(-1000.0f, 0.0f, -1000.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f), vec3(0, 1, 0), vec2(0, 0));

	IndexData = new uint16_t[6];
	*IndexData = 0;
	*(IndexData + 1) = 2;
	*(IndexData + 2) = 1;
	*(IndexData + 3) = 1;
	*(IndexData + 4) = 2;
	*(IndexData + 5) = 3;


	light.DirLightColor = vec4(1, 0, 0, 1.0f);
	light.AmbientColor = vec4(0.9, 0.9, 0.9, 1.0f);
	light.DirLightDirection = vec3(0, -10, 0);

	upPressed = false;
	downPressed = false;
	confirmPressed;


#ifdef _WIN32
	renderer = new WinRenderer();
	renderer->Init();
	renderer->LightingInfo(light);
	canvas = new WinCanvas();
	audioRenderer = new WinAudio();
	getInput = Keyboard::getInstance();


	Mat = new Material(renderer, L"../CommonFiles/Lamborginhi_Aventador_diffuse.jpeg");

	FloorMesh = new WinMesh(VertexData, 4, IndexData, 6, dynamic_cast<WinRenderer*>(renderer)->GetDevice());
	FloorMat = new Material(renderer, L"../CommonFiles/Knockdown_texture.jpg");
	Floor = new GameEntity(FloorMesh, FloorMat);



	LoadScene("../Assets/Scenes/CarScene1.txt");

	skyMesh = new WinMesh("../cube.obj", dynamic_cast<WinRenderer*>(renderer)->GetDevice());
	sky = new GameEntity(skyMesh);

#elif __clang__
	renderer = new PS4Renderer();
	canvas = new PS4Canvas();
	getInput = ControllerInput::getInstance();
	getInput->initialize();
	renderer->Init();

	renderer->LightingInfo(light);

	mesh = new PS4Mesh("/app0/Lamborghini_Aventador.obj", dynamic_cast<PS4Renderer*>(renderer)->GetStackAllocater());
	Mat = new PS4Material(renderer, "/app0/texture.raw");
	entity = new PS4Entity(mesh, Mat);

	FloorMesh = new PS4Mesh(VertexData, 4, IndexData, 6, dynamic_cast<PS4Renderer*>(renderer)->GetStackAllocater());
	FloorMat = new PS4Material(renderer, "/app0/texture.raw");
	Floor = new PS4Entity(FloorMesh, FloorMat);


	//Create a plane mesh and give it to the PS4 canvas, which will then delete it in its destructor
	PS4Canvas *ps4c = static_cast<PS4Canvas*>(canvas);
	//planeMesh = new PS4Mesh(VertexData, 4, IndexData, 6, dynamic_cast<PS4Renderer*>(renderer)->GetStackAllocater());
	planeMesh = new PS4Mesh("/app0/plane.obj", dynamic_cast<PS4Renderer*>(renderer)->GetStackAllocater());
	planeMaterial = new PS4Material(renderer, "/app0/texture.raw");
	planeEntity = new PS4Entity(planeMesh, planeMaterial);
	ps4c->Assign(planeMaterial, dynamic_cast<PS4Renderer*>(renderer)->GetStackAllocater());

#endif 



}



Game::~Game() {

#ifdef _WIN32
	delete sky;
	delete  skyMesh;

#endif
	delete Floor;
	delete  FloorMesh;
	delete  FloorMat;

	delete planeEntity;
	delete planeMesh;
	delete planeMaterial;

	delete[] VertexData;

	delete[] IndexData;
	delete mesh;


	delete renderer;
	delete canvas;
	delete audioRenderer;
	delete Mat;

	for (map<string, IMesh*>::iterator itr = meshes.begin(); itr != meshes.end(); itr++) {
		delete itr->second;
	}

	for (map<string, IEntity*>::iterator itr = entities.begin(); itr != entities.end(); itr++) {
		delete itr->second;
	}
}

void Game::Init()
{

}

void Game::InitializeCanvas() {
#ifdef _WIN32
	WinCanvas *wc = static_cast<WinCanvas*>(canvas);
	WinRenderer *wr = static_cast<WinRenderer*>(renderer);
	wc->AssignDeviceAndContext(wr->GetDevice(), wr->GetContext());
#else
	PS4Canvas *ps4c = static_cast<PS4Canvas*>(canvas);
	PS4Renderer *ps4r = static_cast<PS4Renderer*>(renderer);
#endif
	canvas->Initialize();
}

void Game::Draw()
{

	getInput->update();

	// Draw Floor
	//FloorMat->DatatoShader();
	renderer->DrawMesh(Floor, FloorMat);
#ifdef __clang__
	renderer->DrawMesh((void*)entity, (void*)Mat);
	renderer->DrawMesh((void*)Floor, (void*)FloorMat);
	PS4Canvas *ps4c = static_cast<PS4Canvas*>(canvas);
	ps4c->Render(renderer);
#endif



	for (map<string, IEntity*>::iterator itr = entities.begin(); itr != entities.end(); itr++) {
		renderer->DrawMesh((void*)itr->second, Mat);
	}

#ifdef _WIN32
	renderer->DrawSkyMesh(sky);
	canvas->Render();
#endif
}

void Game::CreateMeshFromFile(string meshName, string path) {
#ifdef _WIN32
	//Create an empty pointer to copy to the mesh map
	IMesh *ptr;
	meshes.insert(std::pair<string, IMesh*>(meshName, ptr));
	meshes[meshName] = new WinMesh(path.c_str(), dynamic_cast<WinRenderer*>(renderer)->GetDevice());
	//meshes[meshName] = new PS4Mesh(path.c_str(), dynamic_cast<PS4Renderer*>(renderer)->GetStackAllocater());
#endif
}

void Game::CreateEntity(string entityName, string meshName) {
#ifdef _WIN32
	IEntity *ptr;
	entities.insert(std::pair<string, IEntity*>(entityName, ptr));
	entities[entityName] = new GameEntity(meshes[meshName], Mat);
	//entities[entityName] = new PS4Entity(meshes[meshName], Mat);
#endif
}

void Game::DestroyEntity(string entityName) {
	delete entities[entityName];
	entities.erase(entityName);
}

void Game::UnloadScene() {
	//for (auto pair : meshes) {
	//	delete pair.second;
	//}

	//for (auto pair : entities) {
	//	delete pair.second;
	//}

	for (map<string, IMesh*>::iterator itr = meshes.begin(); itr != meshes.end(); itr++) {
		delete itr->second;
	}

	for (map<string, IEntity*>::iterator itr = entities.begin(); itr != entities.end(); itr++) {
		delete itr->second;
	}
}

void Game::LoadScene(string filename) {
	UnloadScene();

	ifstream file(filename);
	string str;
	if (file) {
		while (getline(file, str)) {
			SceneObjectData data = Parser::GetSceneObjectData(str);
			//Load meshes
			if (data.type == SceneObjectType::mesh) {
				CreateMeshFromFile(data.name, data.path);
			}
			//Load entities
			else if (data.type == SceneObjectType::entity) {
				CreateEntity(data.name, data.meshID);
				cout << data.x;
				entities[data.name]->setTranslation(data.x, data.y, data.z);
			}
		}
	}
}

void Game::UpdateCanvas() {
	int x = 0;
	int y = 0;
	canvas->Update(0, 0);

	//Up
	if ((getInput->GetKeyDown(0x26) || getInput->isButtonDown(Button::BUTTON_UP)) && !upPressed) {
		upPressed = true;
		canvas->OnPressUp();
	}
	else if (!(getInput->GetKeyDown(0x26) || getInput->isButtonDown(Button::BUTTON_UP))) {
		upPressed = false;
	}

	//Down
	if ((getInput->GetKeyDown(0x28) || getInput->isButtonDown(Button::BUTTON_DOWN)) && !downPressed) {
		downPressed = true;
		canvas->OnPressDown();
	}
	else if (!(getInput->GetKeyDown(0x28) || getInput->isButtonDown(Button::BUTTON_DOWN))) {
		downPressed = false;
	}

	//Return
	if ((getInput->GetKeyDown(0x0D) || getInput->isButtonDown(Button::BUTTON_CROSS)) && !confirmPressed) {
		confirmPressed = true;
		canvas->OnPressConfirm();
	}
	else if (!(getInput->GetKeyDown(0x0D) || getInput->isButtonDown(Button::BUTTON_CROSS))) {
		confirmPressed = false;
	}

	//if ((GetAsyncKeyState(VK_UP) & 0x0001) == 1) {
	//	canvas->OnPressUp();
	//}
	//if ((GetAsyncKeyState(VK_DOWN) & 0x0001) == 1) {
	//	canvas->OnPressDown();
	//}
	//if ((GetAsyncKeyState(VK_RETURN) & 0x0001) == 1) {
	//	canvas->OnPressConfirm();
	//}
}

void Game::Run()
{
	//CreateMeshFromFile("carMesh", "../CommonFiles/Lamborghini_Aventador.obj");
	//CreateEntity("carEntity", "carMesh");
	//CreateEntity("carEntity2", "carMesh");
	//LoadScene("../Assets/Scenes/CarScene1.txt");
	//audioRenderer->Play(audioSound);

	while (!canvas->IsReady()) {
		InitializeCanvas();
	}
//#ifdef _WIN32
//	canvas->LoadScene("../CrossPlatformMain/UIScenes/MenuTest1.txt");
//#else
//	canvas->LoadScene("/app0/UIScenes/MenuTest1.txt");
//#endif
	canvas->LoadScene(ASSETS + (string)"MenuTest1.txt");
	canvas->AssignButtonFunction("smiley1", [&]() {LoadScene("../Assets/Scenes/CarScene1.txt"); });
	canvas->AssignButtonFunction("smiley2", [&]() {LoadScene("../Assets/Scenes/CarScene2.txt"); });
	canvas->AssignButtonFunction("smiley3", [&]() {canvas->LoadScene(ASSETS + (string)"MenuTest2.txt"); });

	while (renderer->MessageExist())
	{
		renderer->BeginFrame();


		if (getInput->GetKeyDown('1')) {
			LoadScene("../Assets/Scenes/CarScene1.txt");
		}
		if (getInput->GetKeyDown('2')) {
			LoadScene("../Assets/Scenes/CarScene2.txt");
		}
		if (getInput->GetKeyDown('W') || getInput->isButtonDown(Button::BUTTON_UP))
		{
			//printf("## square\n");
			renderer->checkInput('w');
			//mesh2->CheckInput(1.0f);

			//entities["carEntity"]->setTranslation(0,0,-10);
			//entities["carEntity"]->moveForward(10);

		}
		if (getInput->GetKeyDown('S') || getInput->isButtonDown(Button::BUTTON_DOWN))
		{
			//printf("## square\n");
			renderer->checkInput('s');
			//mesh2->CheckInput(1.0f);

			//entities["carEntity"]->setTranslation(0, 0, 10);
			//entities["carEntity"]->moveForward(-10);
		}
		if (getInput->GetKeyDown('A') || getInput->isButtonDown(Button::BUTTON_LEFT))
		{
			//printf("## square\n");
			renderer->checkInput('a');
			//mesh2->CheckInput(1.0f);
			//entities["carEntity"]->setRotation(0.1);
		}
		if (getInput->GetKeyDown('D') || getInput->isButtonDown(Button::BUTTON_RIGHT))
		{
			//printf("## square\n");
			renderer->checkInput('d');
			//mesh2->CheckInput(1.0f);
			//entities["carEntity"]->setRotation(-0.1);
		}
		if (getInput->isButtonDown(Button::BUTTON_CIRCLE) || getInput->GetKeyDown('V'))
		{
			printf("## CIRCLE \n");
			//mesh2->CheckInput(2.0f);
		}

		//renderer->camera->cameraPos = entities["carEntity"]->wmTrans + vec3(0, 160, 400);
		//renderer->camera->cameraTarget = entities["carEntity"]->wmTrans;

		UpdateCanvas();
		Draw();

		renderer->EndFrame();
	}

}
