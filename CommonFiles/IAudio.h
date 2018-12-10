#pragma once

//#define audioSound				((char*)"../Assets/Sounds/RollingSpace.wav")


class IAudio
{

public:

	IAudio();
	~IAudio();

	virtual void Init();

	virtual void Play(char *);

	virtual void Graphics();

	virtual void End();
};
