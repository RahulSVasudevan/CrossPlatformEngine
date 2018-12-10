#pragma once

#include "..\CommonFiles\IAudio.h"
#include <sstream>
#include <string>
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#pragma comment(lib,"Winmm.lib")



class WinAudio : public IAudio
{

public:

	WinAudio();
	~WinAudio();

	void Play(char* audioSound);
};