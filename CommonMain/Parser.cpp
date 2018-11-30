//Raises an error if function defined here and not in Parser.h
//#include "Parser.h"
//
//SceneObjectData Parser::GetSceneObjectData(string str) {
//	SceneObjectData data;
//	vector<string> info;
//	string newStr = "";
//	for (int i = 0; i < str.length(); i++) {
//		if (str[i] != ','){
//			newStr += str[i];
//		}
//		else {
//			info.push_back(newStr);
//			newStr = "";
//		}
//	}
//	info.push_back(newStr);
//
//	for (string s : info) {
//		cout << s << endl;
//	}
//	return data;
//}