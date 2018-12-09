#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "SceneObjectData.h"
using namespace std;

class Parser {
public:
	static SceneObjectData GetSceneObjectData(string str) {
		SceneObjectData data;
		vector<string> info;
		string newStr = "";
		for (int i = 0; i < str.length(); i++) {
			if (str[i] != ',') {
				newStr += str[i];
			}
			else {
				info.push_back(newStr);
				newStr = "";
			}
		}
		info.push_back(newStr);

		for (string s : info) {
			if (s.substr(0, 5) == "type=") {
				string test = s.substr(5);
				if (test == "button")
					data.type = SceneObjectType::button;
				else if (test == "listbutton")
					data.type = SceneObjectType::listbutton;
				else if (test == "sprite")
					data.type = SceneObjectType::sprite;
			}
			else if (s.substr(0, 5) == "path=") {
				string a = s.substr(5);
				data.path = wstring(a.begin(), a.end());
			}
			else if (s.substr(0, 5) == "name=") {
				data.name = s.substr(6);
			}
			else if (s.substr(0, 2) == "x=") {
				data.x = stoi(s.substr(2));
			}
			else if (s.substr(0, 2) == "y=") {
				data.y = stoi(s.substr(2));
			}
			else if (s.substr(0, 6) == "width=") {
				data.width = stoi(s.substr(6));
			}
			else if (s.substr(0, 7) == "height=") {
				data.height = stoi(s.substr(7));
			}
		}
		return data;
	}
};