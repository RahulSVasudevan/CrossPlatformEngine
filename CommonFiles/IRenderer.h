#pragma once

#include "IMesh.h"
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
	//virtual void DrawQuad();
	virtual void DrawMesh(void* entity);
	/*virtual void DrawEntity(IEntity* Entity);*/
	virtual void LightingInfo(DirectionalLight light);

};