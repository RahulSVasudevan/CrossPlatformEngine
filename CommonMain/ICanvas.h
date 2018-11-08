#pragma once

#include <string>
using namespace std;

class ICanvas {
public:
	ICanvas() {}
	virtual ~ICanvas() {}
	virtual void Initialize() {}
	virtual void DeInitialize() {}
	virtual void Render() {}

	virtual void CreateTextureFromFile(wstring filename, string textureName) {}
};