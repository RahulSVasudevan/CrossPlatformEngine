
#include "Game.h"



#ifdef _WIN32
	#include "..\WindowsLibrary\WinRenderer.h"
	#include "..\WindowsLibrary\WinMesh.h"
	#include"..\WindowsLibrary\GameEntity.h"
	#include "..\WindowsLibrary\WinAudio.h"
#elif __clang__
	#include "..\PS4Library\PS4Renderer.h"
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
	light.AmbientColor = vec4(0.9, 0.9, 0, 1.0f);
	light.DirLightDirection = vec3(0, 10, 0);


	
	dynamicsWorld = new rp3d::DynamicsWorld(rp3d::Vector3(0, -0.1f, 0));

	//rp3d::Vector3 initPosition(0.0, 3.0, 0.0);
	//rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
	//rp3d::Transform transform(initPosition, initOrientation);

	//rigidbody = dynamicsWorld->createRigidBody(transform);

#ifdef _WIN32
	renderer = new WinRenderer();
	audioRenderer = new WinAudio();
	getInput = Keyboard::getInstance();
	renderer->Init();

	renderer->LightingInfo(light);

	Mat = new Material(renderer, L"../CommonFiles/Lamborginhi_Aventador_diffuse.jpeg");

	FloorMesh = new WinMesh(VertexData, 4, IndexData, 6, dynamic_cast<WinRenderer*>(renderer)->GetDevice());
	FloorMat = new Material(renderer, L"../CommonFiles/Knockdown_texture.jpg");
	Floor = new GameEntity(FloorMesh, FloorMat);
	
	LoadScene("../Assets/Scenes/CarScene1.txt");

	rp3d::Vector3 initPosition(0.0, 0.0, 0.0);
	rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
	rp3d::Transform transform(initPosition, initOrientation);
	entities["carEntity"]->rigidbody = dynamicsWorld->createRigidBody(transform);
	
	Floor->rigidbody = dynamicsWorld->createRigidBody(transform);

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

	delete Floor;
	delete  FloorMesh;
	delete  FloorMat;
	
	
	delete[] VertexData;

	delete[] IndexData;
	//delete rigidbody;
	delete dynamicsWorld;
	delete renderer;
	delete audioRenderer;
	delete Mat;

	//for (auto pair : meshes) {
	//	delete pair.second;
	//}

	for (map<string, IMesh*>::iterator itr = meshes.begin(); itr != meshes.end(); itr++) {
		delete itr->second;
	}

	//for (auto pair : entities) {
	//	delete pair.second;
	//}

	for (map<string, IEntity*>::iterator itr = entities.begin(); itr != entities.end(); itr++) {
		delete itr->second;
	}
}

void Game::Init()
{
	
}

void Game::Draw()
{

	dynamicsWorld->update(0.1f);

	//rp3d::Vector3 pos= rigidbody->getLinearVelocity();
	
	getInput->update();

	// Draw Floor
	FloorMat->DatatoShader();
	renderer->DrawMesh(Floor);

	Mat->DatatoShader();


	for (map<string, IEntity*>::iterator itr = entities.begin(); itr != entities.end(); itr++) {
		renderer->DrawMesh((void*)itr->second);
	}
}

void Game::CreateMeshFromFile(string meshName, string path) {
#ifdef _WIN32
	//Create an empty pointer to copy to the mesh map
	IMesh *ptr;
	meshes.insert(std::pair<string, IMesh*>(meshName, ptr));
	meshes[meshName] = new WinMesh(path.c_str(), dynamic_cast<WinRenderer*>(renderer)->GetDevice());
#endif
}

void Game::CreateEntity(string entityName, string meshName) {
#ifdef _WIN32
	IEntity *ptr;
	entities.insert(std::pair<string, IEntity*>(entityName, ptr));
	entities[entityName] = new GameEntity(meshes[meshName], Mat);
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

void Game::Run()
{
	//CreateMeshFromFile("carMesh", "../CommonFiles/Lamborghini_Aventador.obj");
	//CreateEntity("carEntity", "carMesh");
	//CreateEntity("carEntity2", "carMesh");
	//LoadScene("../Assets/Scenes/CarScene1.txt");
	audioRenderer->Play(audioSound);
	while (renderer->MessageExist())
	{
		renderer->BeginFrame();
	

		
		if (getInput->GetKeyDown('2')) {
			LoadScene("../Assets/Scenes/CarScene2.txt");
		}
		if (getInput->GetKeyDown('W') || getInput->isButtonDown(Button::BUTTON_SQUARE))
		{
			//printf("## square\n");
			//renderer->checkInput('w');
			//mesh2->CheckInput(1.0f);

			//entities["carEntity"]->setTranslation(0,0,-10);
			entities["carEntity"]->moveForward(10);

		}
		if (getInput->GetKeyDown('S') || getInput->isButtonDown(Button::BUTTON_SQUARE))
		{
			//printf("## square\n");
			//renderer->checkInput('s');
			//mesh2->CheckInput(1.0f);

			//entities["carEntity"]->setTranslation(0, 0, 10);
			entities["carEntity"]->moveForward(-10);
		}
		if (getInput->GetKeyDown('A') || getInput->isButtonDown(Button::BUTTON_SQUARE))
		{
			//printf("## square\n");
			//renderer->checkInput('a');
			//mesh2->CheckInput(1.0f);
			entities["carEntity"]->setRotation(0.1);
		}
		if (getInput->GetKeyDown('D') || getInput->isButtonDown(Button::BUTTON_SQUARE))
		{
			//printf("## square\n");
			//renderer->checkInput('d');
			//mesh2->CheckInput(1.0f);
			entities["carEntity"]->setRotation(-0.1);
		}
		if (getInput->isButtonDown(Button::BUTTON_CIRCLE) || getInput->GetKeyDown('V'))
		{
			printf("## CIRCLE \n");
			//mesh2->CheckInput(2.0f);
		}

		renderer->camera->cameraPos = entities["carEntity"]->wmTrans + vec3(0, 160, 400);
		renderer->camera->cameraTarget = entities["carEntity"]->wmTrans;
		//renderer->camera->GetViewMatrix();
		

		Draw();

		renderer->EndFrame();
	}

}
