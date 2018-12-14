#include "WinCanvas.h"

WinCanvas::WinCanvas() {
	containsMenuList = false;
	menuListIndex = 0;
	menuListSize = 0;
	selectedMenuButton = "";
}

//WinCanvas::WinCanvas(ID3D11Device *device, ID3D11DeviceContext *context) {
//	this->device = device;
//	this->context = context;
//}

//This should be the proper way to deallocate a map
WinCanvas::~WinCanvas() {
	for (map<string, ID3D11ShaderResourceView*>::iterator itr = shaderResourceViews.begin(); itr != shaderResourceViews.end(); itr++) {
		//delete itr->second;
		//Release SRVs pointers
		itr->second->Release();
	}
	spriteBatch.reset();
	spriteFont.reset();
	//Function maps should be released automatically
}

bool MouseIsOnButton(UIElementInfo &info, int mousex, int mousey) {
	//TODO: Hover detection seems a little off
	return (mousex > info.x - (info.width / 2) && mousex < info.x + (info.width / 2) &&
		mousey > info.y - (info.height / 2) && mousey < info.y + (info.height / 2));
}

bool MouseButtonDown() {
	return (GetKeyState(VK_LBUTTON) & 0x8000);
}

void WinCanvas::Initialize() {
	spriteBatch.reset(new SpriteBatch(context));
	spriteFont.reset(new SpriteFont(device, L"../Assets/Fonts/calibri.spritefont", false));
}

void FunctionTest() {
	std::cout << "Hi";
}

void WinCanvas::Update(int mousex, int mousey) {
	this->mousex = mousex;
	this->mousey = mousey;

	if (MouseButtonDown()) {
		if (!mouseButtonDown) {
			mouseButtonDown = true;
			mouseButtonUp = false;
			mouseButtonPressed = true;
		}
	}
	else {
		if (mouseButtonDown) {
			mouseButtonDown = false;
			mouseButtonUp = true;
			mouseButtonReleased = true;
		}
	}

	for (map<string, UIElementInfo>::iterator itr = uiElementInfo.begin(); itr != uiElementInfo.end(); itr++) {

		//Buttons
		if (itr->second.type == SceneObjectType::button) {
			itr->second.hovered = MouseIsOnButton(itr->second, mousex, mousey);
			if (itr->second.hovered && mouseButtonPressed) {
				itr->second.pressed = true;
			}

			//When the mouse is released
			if (mouseButtonReleased) {

				//If the button is actually pressed
				if (itr->second.hovered && itr->second.pressed) {
					//FunctionTest();

					//Execute a function if one has been assigned to the button
					if (uiButtonFunctions.count(itr->second.key)) {
						uiButtonFunctions[itr->second.key]();
					}
				}
				itr->second.pressed = false;
			}
		}

		//Menu buttons
		else if (itr->second.type == SceneObjectType::listbutton) {
			itr->second.hovered = (itr->second.index == menuListIndex);
			if (itr->second.hovered) selectedMenuButton = itr->second.key;
		}
	}

	mouseButtonPressed = false;
	mouseButtonReleased = false;

}

void WinCanvas::DeInitialize() {

}

//In the future, should create SRV files and render them on screen separately
void WinCanvas::Render() {
	if (device == nullptr || context == nullptr) return;
	CommonStates states(device);
	spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	SimpleMath::Vector2 pos = SimpleMath::Vector2(80.0f, 80.0f);
	spriteFont->DrawString(spriteBatch.get(), L"Hello", pos);

	XMVECTOR color;

	for (map<string, ID3D11ShaderResourceView*>::iterator itr = shaderResourceViews.begin(); itr != shaderResourceViews.end(); itr++) {
		if (uiElementInfo.size() == 0) { cout << "Empty"; }
		//TODO: make conditions for buttons
		RECT tempRect;
		UIElementInfo info = uiElementInfo[itr->first];
		//info->height = 30;
		//info->width = 30;
		//info->x = 50;
		//info->y = 50;
		//info->hovered = false;
		//info->key = itr->first;
		//info->pressed = false;

		//Determine how sprite dimming should work
		if (info.type == SceneObjectType::button) {
			if (!info.hovered) {
				color = Colors::White;
			}
			else {
				color = (info.pressed) ? Colors::Gray : Colors::LightGray;
			}
		}
		else if (info.type == SceneObjectType::listbutton) {
			color = (info.hovered) ? Colors::White : Colors::Gray;
		}

		tempRect.bottom = info.y + (info.height / 2);
		tempRect.top = info.y - (info.height / 2);
		tempRect.left = info.x - (info.width / 2);
		tempRect.right = info.x + (info.width / 2);
		spriteBatch->Draw(itr->second, tempRect, color);
	}


	spriteBatch->End();
	context->OMSetBlendState(0, 0, 0xFFFFFFFF);
	context->OMSetDepthStencilState(0, 0);
}

void WinCanvas::AssignDeviceAndContext(ID3D11Device *device, ID3D11DeviceContext *context) {
	this->device = device;
	this->context = context;
}

void WinCanvas::LoadScene(string filename) {
	UnloadScene();

	ifstream file(filename);
	string str;
	if (file) {
		//cout << "Loading file " << filename;
		while (getline(file, str)) {
			UISceneObjectData data = Parser::GetUISceneObjectData(str);
			//TODO: Implement error handling
			CreateTextureFromFile(data.path, data.name, data.x, data.y, data.width, data.height, data.index, data.type);
		}
	}
}

void WinCanvas::UnloadScene() {
	//Release SRVs pointers
	for (map<string, ID3D11ShaderResourceView*>::iterator itr = shaderResourceViews.begin(); itr != shaderResourceViews.end(); itr++) {
		itr->second->Release();
	}
	shaderResourceViews.clear();
	//TODO: Clearing UI Element info causes an error. Fix.
	//uiElementInfo.clear();
	uiButtonFunctions.clear();

	containsMenuList = false;
	menuListIndex = 0;
	menuListSize = 0;
	selectedMenuButton = "";
}

void WinCanvas::OnPressUp() {
	menuListIndex--;
	if (menuListIndex < 0)
		menuListIndex += menuListSize;
}
void WinCanvas::OnPressDown() {
	menuListIndex++;
	if (menuListIndex >= menuListSize)
		menuListIndex -= menuListSize;
}
void WinCanvas::OnPressLeft() {

}
void WinCanvas::OnPressRight() {

}
void WinCanvas::OnPressConfirm() {
	//cout << selectedMenuButton;
	if (uiButtonFunctions.count(selectedMenuButton)) {
		uiButtonFunctions[selectedMenuButton]();
	}
}
void WinCanvas::OnPressBack() {

}

//Not sure if proper way to add pointers into maps
//For testing purposes
void WinCanvas::CreateTextureFromFile(wstring filename, string textureName) {
	if (device == nullptr || context == nullptr) return;
	if (shaderResourceViews[textureName] != nullptr) return;

	ID3D11ShaderResourceView *ptr;
	shaderResourceViews.insert(std::pair<string, ID3D11ShaderResourceView*>(textureName, ptr));
	CreateWICTextureFromFile(device, filename.c_str(), nullptr, &shaderResourceViews[textureName]);
	string str = string(filename.begin(), filename.end());

	UIElementInfo info;
	info.key = textureName;
	info.x = 50;
	info.y = 50;
	info.width = 25;
	info.height = 25;
	info.hovered = false;
	info.pressed = false;
	info.index = 0;
	info.type = SceneObjectType::sprite;
	uiElementInfo.insert(std::pair<string, UIElementInfo>(textureName, info));
	//uiButtonFunctions.insert(std::pair<string, std::function<void()>>(textureName, FunctionTest));
}

//Called by the scene loader
void WinCanvas::CreateTextureFromFile(wstring filename, string textureName, int x, int y, int width, int height, int index, SceneObjectType type) {
	if (device == nullptr || context == nullptr) return;
	if (shaderResourceViews[textureName] != nullptr) return;

	ID3D11ShaderResourceView *ptr;
	shaderResourceViews.insert(std::pair<string, ID3D11ShaderResourceView*>(textureName, ptr));
	CreateWICTextureFromFile(device, filename.c_str(), nullptr, &shaderResourceViews[textureName]);
	string str = string(filename.begin(), filename.end());

	UIElementInfo info;
	info.key = textureName;
	info.x = x;
	info.y = y;
	info.width = width;
	info.height = height;
	info.hovered = false;
	info.pressed = false;
	info.index = index;
	info.type = type;
	if (uiElementInfo.count(textureName)) {
		uiElementInfo.erase(textureName);
	}
	uiElementInfo.insert(std::pair<string, UIElementInfo>(textureName, info));
	//TODO: Let the Game assign individual functions to buttons
	if (info.index == 0) {
		AssignButtonFunction(textureName, [&]() {LoadScene("../Assets/Scenes/MenuTest2.txt"); });
	}
	else if (info.index == 1) {
		AssignButtonFunction(textureName, [&]() {LoadScene("../Assets/Scenes/MenuTest1.txt"); });
	}
	//uiButtonFunctions.insert(std::pair<string, std::function<void()>>(textureName, FunctionTest));
	//AssignButtonFunction(str, FunctionTest);

	if (type == SceneObjectType::listbutton) {
		menuListSize++;
	}
}

void WinCanvas::AssignButtonFunction(string buttonName, function<void()> func) {
	if (uiButtonFunctions.count(buttonName)) {
		uiButtonFunctions.erase(buttonName);
	}
	uiButtonFunctions.insert(std::pair<string, std::function<void()>>(buttonName, func));
}

bool WinCanvas::IsReady() {
	return (this->device != nullptr && this->context != nullptr);
}