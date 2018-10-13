#pragma once

class IRenderer
{

	int x;

public:

	IRenderer();
	virtual int Test();
	virtual void Init();
	virtual void MessageLoop();

	IRenderer* NewPlatformRenderer();
	//void CreateConsoleWindow();

};