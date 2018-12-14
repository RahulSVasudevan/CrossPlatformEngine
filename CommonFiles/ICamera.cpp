//#include "../WindowsLibrary/stdafx.h"
#include "ICamera.h"



ICamera::ICamera()
{
}


ICamera::~ICamera()
{
}

void ICamera::InitialiseCamera(int h, int w)
{
	int height = h;
	int width = w;

#ifdef _WIN32
	cameraPos = glm::vec3(0, 160, 400);
#else
	cameraPos = glm::vec3(0.0f, 0.0f, 20.0f);	
#endif

	cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
	//cameraDirection = glm::normalize(cameraPos - cameraTarget);
	//cameraDirection = glm::vec3(0.0f, -0.5f, -1.0f);

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	//front = glm::vec3(0.0f, 0.0f, 1.0f);
	cameraRight = glm::normalize(glm::cross(up, cameraTarget));

	//cameraUp = glm::cross(cameraDirection, cameraRight);

	//cameraFront = glm::cross(cameraUp, cameraRight);

	viewMatrix = glm::lookAt(cameraPos,
		cameraPos + cameraTarget,
		up);

	viewMatrix = glm::transpose(viewMatrix);

	worldMatrix = glm::mat4(1.0f);

	projectionMatrix = glm::perspective(45.0f * 3.1415926535f / 180.0f, (float)height / width, 0.1f, 10000.0f);

	projectionMatrix = glm::transpose(projectionMatrix);
}

void ICamera::MakeViewMatrix()
{
	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraTarget, up);
	viewMatrix = glm::transpose(viewMatrix);
}

glm::mat4x4 ICamera::GetViewMatrix()
{
	return viewMatrix;
}

glm::mat4x4 ICamera::GetWorldMatrix()
{
	return worldMatrix;
}

glm::mat4x4 ICamera::GetProjectionMatrix()
{
	return projectionMatrix;
}

glm::mat4x4 ICamera::GetViewProjMatrix()
{
	return viewMatrix * projectionMatrix;
}

void ICamera::moveFront()
{
	cameraPos += (cameraSpeed * cameraTarget);
	MakeViewMatrix();
}

void ICamera::moveBack()
{
	cameraPos -= (cameraSpeed * cameraTarget);
	MakeViewMatrix();
}

void ICamera::moveLeft()
{
	cameraRight = glm::normalize(glm::cross(up, cameraTarget));
	cameraPos += cameraRight * cameraSpeed;
	MakeViewMatrix();
}

void ICamera::moveRight()
{
	cameraRight = glm::normalize(glm::cross(up, cameraTarget));
	cameraPos -= cameraRight * cameraSpeed;
	MakeViewMatrix();
}
