#pragma once
class InputEvent
{
public:
	enum EventType {
		Press,
		Release,
		Invalid
	};
	InputEvent();
	InputEvent(const EventType type, const unsigned char key);
	~InputEvent();
	bool isKeyPressed() const;
	bool isKeyReleased() const;
	bool isValid() const;
	unsigned char getKey() const;
private:
	EventType type;
	unsigned char key;
};

