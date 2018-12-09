#pragma once

#include "../CommonFiles/Maths.h"
#include "../WindowsLibrary/Material.h"
#include"../WindowsLibrary/WinMesh.h"
#include"../WindowsLibrary/WinRenderer.h"
#include"../CommonFiles/IRenderer.h"
using namespace glm;
class IEntity {
public:
	IEntity();
	IEntity(IMesh* m, IRenderer* renderer);
	~IEntity();
	virtual void InitializeMaterial();
	virtual Material* getMaterial();
};