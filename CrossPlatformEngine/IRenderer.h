#pragma once

class IRenderer
{

	int x;

public:

	IRenderer();
	virtual int Test();
	virtual void Init();
	virtual void MessageLoop();
	virtual bool MessageExist();
	virtual void EndFrame();
	virtual void DrawQuad();

	IRenderer* NewPlatformRenderer();
	//void CreateConsoleWindow();

};