

#include "stdafx.h"
#include "WinRenderer.h"
#include "IRenderer.h"


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

	return new WinRenderer();

}
