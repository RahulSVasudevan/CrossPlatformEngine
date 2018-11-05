#pragma once

#include "Transform.h"
#include <unordered_set>
using namespace std;

class GameObject
{
public:
	GameObject();
	GameObject(Vector3 position, Vector3 scale, Quaternion rotation);
	~GameObject();
private:
	Transform transform;
	unordered_set<int> meshIDs;
};