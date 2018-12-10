#pragma once

#include "IMesh.h"
#include "ICamera.h"
class IRenderer
{


public:

	IRenderer();
	virtual ~IRenderer();
	virtual void Init();
	virtual void MessageLoop();
	virtual bool MessageExist();
	virtual void BeginFrame();
	virtual void EndFrame();
	ICamera * camera;
	//virtual void DrawQuad();
	virtual void DrawMesh(void* entity);
	/*virtual void DrawEntity(IEntity* Entity);*/
	virtual void LightingInfo(DirectionalLight light);
	virtual void checkInput(char);
};