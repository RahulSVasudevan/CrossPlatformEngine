#pragma once

#include "IMesh.h"
//#include"../WindowsLibrary/Material.h"
//#include"../WindowsLibrary/GameEntity.h"
class IRenderer
{

	//Material* x;
public:

	IRenderer();
	virtual ~IRenderer();
	virtual void Init();
	virtual void MessageLoop();
	virtual bool MessageExist();
	virtual void EndFrame();
	virtual void DrawQuad();
	virtual void DrawMesh(IMesh* Mesh);
	virtual void LightingInfo(DirectionalLight light);
	//virtual Material* getMaterial();
};