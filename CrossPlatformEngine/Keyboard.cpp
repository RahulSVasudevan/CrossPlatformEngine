#include "stdafx.h"
#include "Keyboard.h"
#include<iostream>

Keyboard::Keyboard()
{
	for (int i = 0; i < 256; i++)
	{
		this->keyStates[i] = false;// Initializing all key states to off
	}
}


Keyboard::~Keyboard()
{
}

bool Keyboard::KeyIsPressed(const unsigned char keycode)
{
	return this->keyStates[keycode];
}

bool Keyboard::KeyBufferIsEmpty()
{
	return this->keyBuffer.empty();
}

bool Keyboard::CharBufferIsEmpty()
{
	return this->charBuffer.empty();
}

InputEvent Keyboard::ReadKey()
{
	if (this->keyBuffer.empty()) //if no keys to read
	{
		return InputEvent();//call default constructor in inputevent
	}
	else
	{
		InputEvent i = this->keyBuffer.front(); // get first input event from queue
		this->keyBuffer.pop(); // remove item from queue
		return i; // return input event
	}
}

unsigned char Keyboard::ReadChar()
{
	if (this->keyBuffer.empty()) //if no keys to read
	{
		return 0u;//return 0
	}
	else
	{
		unsigned char c = this->charBuffer.front(); // get first input event from queue
		this->charBuffer.pop(); // remove item from queue
		return c; // return char
	}
}

void Keyboard::OnKeyPressed(const unsigned char key)
{
	this->keyStates[key] = true;
	this->keyBuffer.push(InputEvent(InputEvent::EventType::Press, key));
	/*while (!keyBuffer.empty())
	{
		std::cout <<"printsomething" << std::endl;
		keyBuffer.pop();
	}
	*/
}

void Keyboard::OnKeyReleased(const unsigned char key)
{
	this->keyStates[key] = false;
	this->keyBuffer.push(InputEvent(InputEvent::EventType::Release, key));
}

void Keyboard::OnChar(const unsigned char key)
{
	this->charBuffer.push(key);
}

void Keyboard::EnableAutoRepeatKeys()
{
	this->autoRepeatKey = true;
}

void Keyboard::DisableAutoRepeatKeys()
{
	this->autoRepeatKey = false;
}

void Keyboard::EnableAutoRepeatChars()
{
	this->autoRepeatChar = true;
}

void Keyboard::DisableAutoRepeatChars()
{
	this->autoRepeatChar = false;
}

bool Keyboard::IsKeyAutoRepeat()
{
	return this->autoRepeatKey;
}

bool Keyboard::isCharsAutoRepeat()
{
	return this->autoRepeatChar;
}
