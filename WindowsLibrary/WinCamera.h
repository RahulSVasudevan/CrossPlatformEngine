#pragma once

#include "../CommonFiles/ICamera.h"



class WinCamera : public ICamera
{
public:
	WinCamera();
	virtual ~WinCamera();

	void InitialiseCamera(int height, int width);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetWorldMatrix();
	glm::mat4 GetProjectionMatrix();

};

