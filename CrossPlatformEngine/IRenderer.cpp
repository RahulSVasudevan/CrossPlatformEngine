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
#ifdef WIN32
	return new WinRenderer();
#endif
}
