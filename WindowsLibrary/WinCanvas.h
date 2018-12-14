#pragma once

#include "UIElementInfo.h"
#include "../packages/directxtk_desktop_2015.2018.11.20.1/include/CommonStates.h"
#include <d3d11.h>
#include "../CommonFiles/ICanvas.h"
#include <iostream>
#include <functional>
#include <fstream>
#include <map>
#include "../CommonFiles/SceneObjectData.h"
#include "../CommonFiles/Parser.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include <string>
#include "WICTextureLoader.h"
#include <mutex>

using namespace DirectX;
using namespace std;

class WinCanvas : public ICanvas {
public:
	WinCanvas();
	//WinCanvas(ID3D11Device *device, ID3D11DeviceContext *context);
	~WinCanvas();
	void Initialize();
	void DeInitialize();
	void Update(int mousex, int mousey);
	void Render();

	void AssignDeviceAndContext(ID3D11Device *device, ID3D11DeviceContext *context);

	//textureName, to be looked up in map
	void LoadScene(string filename);
	void UnloadScene();

	//Input functions
	void OnPressUp();
	void OnPressDown();
	void OnPressLeft();
	void OnPressRight();
	void OnPressConfirm();
	void OnPressBack();

	void CreateTextureFromFile(wstring filename, string textureName);
	void CreateTextureFromFile(wstring filename, string textureName, int x, int y, int width, int height, int index, SceneObjectType type);
	void AssignButtonFunction(string buttonName, function<void()> func);
	bool IsReady();

private:
	ID3D11Device * device;
	ID3D11DeviceContext *context;
	unique_ptr<SpriteBatch> spriteBatch;
	unique_ptr<SpriteFont> spriteFont;
	int mousex;
	int mousey;
	bool mouseButtonPressed;
	bool mouseButtonReleased;
	bool mouseButtonDown;
	bool mouseButtonUp;

	map<string, ID3D11ShaderResourceView*> shaderResourceViews;
	map<string, UIElementInfo> uiElementInfo;
	map<string, std::function<void()>> uiButtonFunctions;

	bool containsMenuList;
	int menuListIndex;
	int menuListSize;
	string selectedMenuButton;
};