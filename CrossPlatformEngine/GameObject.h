#pragma once

#include "Transform.h"

class GameObject
{
public:
	GameObject();
	GameObject(Vector3 position, Vector3 scale, Quaternion rotation);
	~GameObject();
private:
	Transform transform;
	int meshCount;
	int *meshIDs;
};