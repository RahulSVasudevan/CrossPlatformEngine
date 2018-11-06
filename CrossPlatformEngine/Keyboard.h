#pragma once
#include"InputEvent.h"
#include<Windows.h>
#include<queue>
class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	static Keyboard* getInstance()
	{
		static Keyboard* instance = NULL;
		if (instance == NULL)
		{
			instance = new Keyboard;
		}
		_ASSERT(instance);

		return instance;
	}

	bool KeyIsPressed(const unsigned char keycode);
	bool KeyBufferIsEmpty();
	bool CharBufferIsEmpty();
	InputEvent ReadKey();
	unsigned char ReadChar();
	void OnKeyPressed(const unsigned char key);
	void OnKeyReleased(const unsigned char key);
	void OnChar(const unsigned char key);
	void EnableAutoRepeatKeys();
	void DisableAutoRepeatKeys();
	void EnableAutoRepeatChars();
	void DisableAutoRepeatChars();
	bool IsKeyAutoRepeat();
	bool isCharsAutoRepeat();

private:
	bool autoRepeatKey = false;
	bool autoRepeatChar = false;
	bool keyStates[256];
	std::queue<InputEvent> keyBuffer;
	std::queue<unsigned char> charBuffer;
};