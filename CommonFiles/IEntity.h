#pragma once

#include"../CommonFiles/IMaterial.h"
using namespace glm;
class IEntity {

public:
	IEntity();
	IEntity(IMesh* m, IMaterial* mat);
	virtual void setTranslation(float, float, float) {};
	virtual void setScale(float, float, float) {};
	virtual void setRotation(float) {};
	virtual void moveForward(float speed) {};
	~IEntity();
};