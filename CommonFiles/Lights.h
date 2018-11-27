#pragma once

#include "Maths.h"

using namespace glm;

struct DirectionalLight
{
	vec4 AmbientColor;
	vec4 DiffuseColor;
	vec3 Direction;
};