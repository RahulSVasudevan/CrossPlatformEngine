
#include "IRenderer.h"


IRenderer::IRenderer()
{
	camera = new ICamera();
}

IRenderer::~IRenderer()
{
	delete camera;
}


void IRenderer::Init()
{
}

void IRenderer::MessageLoop()
{
}


bool IRenderer::MessageExist()
{
	return true;
}

void IRenderer::BeginFrame()
{
}

void IRenderer::EndFrame()
{
}

//void IRenderer::DrawQuad()
//{
//}

void IRenderer::DrawMesh(IMesh* Mesh)
{
}

void IRenderer::LightingInfo(DirectionalLight light)
{
}


void IRenderer::checkInput(char)
{
}
