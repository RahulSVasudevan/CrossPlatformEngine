#pragma once

#include "CommonStates.h"
#include <d3d11.h>
#include "../CommonMain/ICanvas.h"
#include <iostream>
#include <functional>
#include <map>
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include <string>
#include "WICTextureLoader.h"

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
	void CreateTextureFromFile(wstring filename, string textureName);

private:
	ID3D11Device * device;
	ID3D11DeviceContext *context;
	unique_ptr<SpriteBatch> spriteBatch;
	unique_ptr<SpriteFont> spriteFont;
	int mousex;
	int mousey;

	map<string, ID3D11ShaderResourceView*> shaderResourceViews;
};