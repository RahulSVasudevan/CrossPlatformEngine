#pragma once

#include <string>
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
	
	//Probably more efficient to use optional parameters (x = 0), if possible in C++
	virtual void CreateTextureFromFile(wstring filename, string textureName) = 0;
	virtual void CreateTextureFromFile(wstring filename, string textureName, int x, int y, int width, int height) {};
	virtual void CreateButtonFromFile(wstring filename, string textureName) {}	//Shouldn't cause an error on the PS4 side

	virtual bool IsReady() { return false; }
};