#pragma once

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



};