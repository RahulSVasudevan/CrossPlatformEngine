#pragma once

#include <fstream>
#include <string>

enum SceneObjectType {
	sprite = 0,
	button
};

struct SceneObjectData {
	std::wstring path;
	std::string name;
	int x;
	int y;
	int width;
	int height;
	SceneObjectType type;
};