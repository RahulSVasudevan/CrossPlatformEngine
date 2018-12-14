#pragma once
#include"../CommonFiles/Input.h"
#include"InputEvent.h"
#include<Windows.h>
#include<queue>
class Keyboard : public Input
{
public:
	Keyboard();
	~Keyboard();

	static Keyboard* getInstance()
	{
		static Keyboard* instance = NULL;
		if (instance == NULL)
		{
			instance = new Keyboard();
		}
		return instance;
	}

	bool GetKeyDown(const unsigned char keycode)override;
	bool KeyBufferIsEmpty();
	bool CharBufferIsEmpty();
	InputEvent ReadKey();
	unsigned char ReadChar();
	void OnKeyPressed(const unsigned char key);
	void OnKeyReleased(const unsigned char key);
	void OnChar(const unsigned char key);
	bool keyStates[256];
	void update()override;
private:
	std::queue<InputEvent> keyBuffer;
	std::queue<unsigned char> charBuffer;
};