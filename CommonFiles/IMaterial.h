#pragma once
#include"../CommonFiles/IRenderer.h"
using namespace glm;
class IMaterial {

public:
	IMaterial();
	IMaterial(IRenderer*, const wchar_t * obj);
	~IMaterial();
	//virtual void LoadTextures(const char * obj);
	virtual void DatatoShader();
};
