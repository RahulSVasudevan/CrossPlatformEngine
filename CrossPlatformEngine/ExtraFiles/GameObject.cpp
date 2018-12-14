#include "stdafx.h"
#include "GameObject.h"

//Probably a way to combine these 2 constructors into one
GameObject::GameObject() {
	transform.position = Vector3{ 0, 0, 0 };
	transform.scale = Vector3{ 0, 0, 0 };
	transform.rotation = Quaternion{ 0, 0, 0, 0 };
}

GameObject::GameObject(Vector3 position, Vector3 scale, Quaternion rotation) {
	transform.position = position;
	transform.scale = scale;
	transform.rotation = rotation;
}

GameObject::~GameObject() {
	meshIDs.clear();
}