#include "../WindowsLibrary/stdafx.h"
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

	/*
	// Temp Code
	vec3 cameraPos = vec3(0.0f, 160.0f, 400.0f);
	vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);
	//vec3 cameraDirection = normalize(cameraPos - cameraTarget);
	vec3 cameraDirection = vec3(0.0f,-0.5f,-1.0f);
	vec3 up = vec3(0.0f, 1.0f, 0.0f);
	vec3 cameraRight = normalize(cross(up, cameraDirection));

	viewMatrix = lookAt(cameraPos, cameraTarget, up);
	viewMatrix = transpose(viewMatrix);
	worldMatrix = mat4(1.0f);

	projectionMatrix = perspective(0.25f * 3.1415926535f, (float)width / height, 0.1f, 1000.0f);
	projectionMatrix = transpose(projectionMatrix);

	*/

	cameraPos = glm::vec3(0.0f, 160.0f, 400.0f);

	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	//cameraDirection = glm::normalize(cameraPos - cameraTarget);
	cameraDirection = glm::vec3(0.0f, -0.5f, -1.0f);

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	cameraUp = glm::cross(cameraDirection, cameraRight);

	viewMatrix = glm::lookAt(cameraPos,
		cameraTarget,
		up);

	viewMatrix = glm::transpose(viewMatrix);

	worldMatrix = glm::mat4(1.0f);

	projectionMatrix = glm::perspective(0.25f * 3.1415926535f, (float)height / width, 0.1f, 1000.0f);

	projectionMatrix = glm::transpose(projectionMatrix);
}

void ICamera::MakeViewMatrix()
{
	viewMatrix = glm::lookAt(cameraPos,
		cameraPos + cameraTarget,
		up);
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

void ICamera::moveFront()
{
	cameraPos += cameraSpeed * cameraTarget;
	MakeViewMatrix();
}
