#pragma once
#include"../CommonFiles/IRenderer.h"
using namespace glm;
class IMaterial {
public:
	IMaterial();
	~IMaterial();
	virtual void LoadTextures();
	virtual void DatatoShader();
};
