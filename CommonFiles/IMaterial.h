#pragma once
#include"../CommonFiles/IRenderer.h"
using namespace glm;
class IMaterial {

public:
	IMaterial();
	IMaterial(IRenderer*, const char * obj);
	virtual ~IMaterial();
	//virtual void LoadTextures(const char * obj);
	virtual void DatatoShader();
};
