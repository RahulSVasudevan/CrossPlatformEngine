#pragma once
//#include "../WindowsLibrary/stdafx.h"
#include "../CommonFiles/glm/glm.hpp"
#include "../CommonFiles/glm/gtc/matrix_transform.hpp"
#include "../CommonFiles/glm/gtc/type_ptr.hpp"

//#include "../WindowsLibrary/SimpleShader.h"



class ICamera
{
public:
	ICamera();

	virtual ~ICamera();

	virtual void InitialiseCamera(int height, int width);

	void MakeViewMatrix();

	glm::mat4x4 GetViewMatrix();

	glm::mat4x4 GetWorldMatrix();

	glm::mat4x4 GetProjectionMatrix();

	void moveFront();
	void moveBack();
	void moveLeft();
	void moveRight();

	float cameraSpeed = 0.5f;
	glm::vec3 cameraPos;

	glm::vec3 cameraTarget;

	glm::vec3 cameraDirection;
	glm::vec3 up;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::mat4 viewMatrix;
	glm::mat4 worldMatrix;
	glm::mat4 projectionMatrix;
	
};
