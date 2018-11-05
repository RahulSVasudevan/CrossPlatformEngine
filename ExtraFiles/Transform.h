#pragma once

#include "Vector3.h"
#include "Quaternion.h"

struct Transform {
	Vector3 position;
	Vector3 scale;
	Quaternion rotation;
};