
#include "stdafx.h"
#include "WinRenderer.h"
#include "IRenderer.h"


IRenderer::IRenderer()
{
}

IRenderer::~IRenderer()
{
	

//#ifdef _WIN32
//	WinRenderer* win = reinterpret_cast<WinRenderer*>(this);
//	//delete win;
//#endif
}


void IRenderer::Init()
{
}

void IRenderer::MessageLoop()
{
}


bool IRenderer::MessageExist()
{
	return false;
}

void IRenderer::EndFrame()
{
}

void IRenderer::DrawQuad()
{
}

IRenderer * IRenderer::NewPlatformRenderer()
{
#ifdef _WIN32
	return new WinRenderer();
#endif
}
