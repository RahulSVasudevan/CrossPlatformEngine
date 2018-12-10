#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "SceneObjectData.h"
using namespace std;

class Parser {
public:
	static vector<string> ParseLine(string str) {
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

		return info;
	}
	static SceneObjectData GetSceneObjectData(string str) {
		//Create data and initialize with default values
		SceneObjectData data;
		data.path = "";
		data.meshID = "";
		data.name = "";
		data.x = 0;
		data.y = 0;
		data.z = 0;
		data.type = SceneObjectType::none;

		vector<string> info = ParseLine(str);

		for (string s : info) {
			if (s.substr(0, 5) == "type=") {
				string test = s.substr(5);
				if (test == "mesh") {
					data.type = SceneObjectType::mesh;
				}
				else if (test == "entity") {
					data.type = SceneObjectType::entity;
				}
			}
			else if (s.substr(0, 7) == "meshID=") {
				data.meshID = s.substr(7);
			}
			else if (s.substr(0, 5) == "path=") {
				data.path = s.substr(5);
			}
			else if (s.substr(0, 5) == "name=") {
				data.name = s.substr(5);
			}
			else if (s.substr(0, 2) == "x=") {
				data.x = stoi(s.substr(2));
			}
			else if (s.substr(0, 2) == "y=") {
				data.y = stoi(s.substr(2));
			}
			else if (s.substr(0, 2) == "z=") {
				data.z = stoi(s.substr(2));
			}
		}
		return data;
	}
	static UISceneObjectData GetUISceneObjectData(string str) {
		//Create data and initialize with default values
		UISceneObjectData data;
		data.path = L"";
		data.name = "";
		data.x = 0;
		data.y = 0;
		data.width = 0;
		data.height = 0;
		data.type = SceneObjectType::none;
		vector<string> info = ParseLine(str);

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