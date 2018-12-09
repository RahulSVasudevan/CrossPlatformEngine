#pragma once

#include "../CommonFiles/Maths.h"
#include"../CommonFiles/IRenderer.h"
#include"../CommonFiles/IMaterial.h"
using namespace glm;
class IEntity {

public:
	IEntity();
	IEntity(IMesh* m, IMaterial* mat);
	~IEntity();
};