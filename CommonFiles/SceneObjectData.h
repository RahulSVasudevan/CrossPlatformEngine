#pragma once

#include <fstream>
#include <string>

using namespace std;

enum SceneObjectType {
	none = 0,
	sprite,
	button,
	listbutton,

	mesh,
	entity,
	material
};

struct SceneObjectData {
	string path;
	string meshID;
	string name;
	float x;
	float y;
	float z;
	SceneObjectType type;
};

struct UISceneObjectData {
	wstring path;
	string name;
	int x;
	int y;
	int width;
	int height;
	int index;
	SceneObjectType type;
};