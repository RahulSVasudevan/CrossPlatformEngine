#include "stdafx.h"
#include "InputEvent.h"
#include<iostream>

InputEvent::InputEvent()
{
	this->type = EventType::Invalid;
	this->key = (0u);
}

InputEvent::InputEvent(const EventType t, const unsigned char k)
{
	type = t;
	key = k;
	std::cout <<type << std::endl;
	std::cout << key << std::endl;
}


InputEvent::~InputEvent()
{
}

bool InputEvent::isKeyPressed() const
{
	return this->type == EventType::Press;
}

bool InputEvent::isKeyReleased() const
{
	return this->type == EventType::Release;
}

bool InputEvent::isValid() const
{
	return this->type != EventType::Invalid;
}

unsigned char InputEvent::getKey() const
{
	return this->key;
}
