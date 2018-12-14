#pragma once

#include "Maths.h"

using namespace glm;

struct DirectionalLight
{
	vec4 AmbientColor;
	vec4 DirLightColor;
	vec3 DirLightDirection;
};

struct PointLight
{
	vec4 PointLightColor;
	vec3 PointLightPosition;
};