#pragma once

#include<cstdint>

class Input
{

public:

	enum ButtonEventPattern
	{
		PATTERN_ANY,
		PATTERN_ALL,
	};

	Input();
	~Input();
	virtual bool GetKeyDown(const unsigned char keycode) { return false; };
	virtual int initialize();
	virtual void update() {};
	virtual bool isButtonDown(uint32_t buttons, ButtonEventPattern pattern = PATTERN_ALL) { return false; };
};

