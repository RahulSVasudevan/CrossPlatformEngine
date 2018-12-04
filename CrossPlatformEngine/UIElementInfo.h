#pragma once

#include <string>
using namespace std;

struct UIElementInfo {
	//Good idea to use strings in structs?, is it better to use strings instead of wstrings?
	string key;
	int x;
	int y;
	int width;
	int height;
	bool hovered;	//Only used by buttons
	bool pressed;
};