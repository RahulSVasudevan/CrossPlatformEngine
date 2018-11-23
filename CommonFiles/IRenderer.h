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
	virtual void EndFrame();
	virtual void DrawQuad();
	virtual void DrawMesh(IMesh* Mesh);

};