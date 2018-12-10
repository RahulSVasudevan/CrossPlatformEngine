
#include "IRenderer.h"


IRenderer::IRenderer()
{
}

IRenderer::~IRenderer()
{

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

void IRenderer::DrawMesh(void* entity)
{
}

//void IRenderer::DrawEntity(IEntity * Entity)
//{
//}

void IRenderer::LightingInfo(DirectionalLight light)
{
}
