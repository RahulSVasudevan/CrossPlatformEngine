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
	virtual void Update(int mousex, int mousey) {}	//Not sure if = 0 would cause an error on PS4 side
	virtual void Render() = 0;

	virtual void CreateTextureFromFile(wstring filename, string textureName) = 0;
};