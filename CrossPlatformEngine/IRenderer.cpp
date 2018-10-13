#include "stdafx.h"
#include "IRenderer.h"
#include "WinRenderer.h"

IRenderer::IRenderer()
{
	x = 1;
}

int IRenderer::Test()
{
	return x;
}

void IRenderer::Init()
{
}

void IRenderer::MessageLoop()
{
}

IRenderer * IRenderer::NewPlatformRenderer()
{
#ifdef WIN32
	return new WinRenderer();
#endif
}
