
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
void IRenderer::DrawSkyMesh(void * entity)
{
}


void IRenderer::DrawMesh(void* entity, void *material)
{
}

//void IRenderer::DrawEntity(IEntity * Entity)
//{
//}

void IRenderer::LightingInfo(DirectionalLight light)
{
}

void IRenderer::checkInput(char)
{
}
