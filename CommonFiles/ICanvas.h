#pragma once

#include "SceneObjectData.h"
#include <string>
#include <functional>
using namespace std;

class ICanvas {
public:
	ICanvas() {}
	virtual ~ICanvas() {}
	virtual void Initialize() = 0;
	virtual void DeInitialize() = 0;
	//If on PS4, mousex and mousey can both be 0
	virtual void Update(int mousex, int mousey) {}
	virtual void Render() = 0;

	virtual void LoadScene(string filename) {}
	virtual void UnloadScene() {}

	//Input functions
	virtual void OnPressUp() {}
	virtual void OnPressDown() {}
	virtual void OnPressLeft() {}
	virtual void OnPressRight() {}
	virtual void OnPressConfirm() {}
	virtual void OnPressBack() {}

	//Probably more efficient to use optional parameters (x = 0), if possible in C++
	virtual void CreateTextureFromFile(wstring filename, string textureName) = 0;
	virtual void CreateTextureFromFile(wstring filename, string textureName, int x, int y, int width, int height, int index, SceneObjectType type) {};
	virtual void CreateButtonFromFile(wstring filename, string textureName) {}	//Shouldn't cause an error on the PS4 side

	virtual void AssignButtonFunction(string buttonName, function<void()> func) {}

	virtual bool IsReady() { return false; }
};