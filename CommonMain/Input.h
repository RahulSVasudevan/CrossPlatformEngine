#pragma once



class Input
{
public:
	Input();
	~Input();
	virtual bool GetKeyDown(const unsigned char keycode);
	
	//bool GetButtonDown(bool button);
};

