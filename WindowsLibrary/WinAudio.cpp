#include "stdafx.h"
#include "WinAudio.h"



WinAudio::WinAudio()
{

}

WinAudio::~WinAudio()
{
}


void WinAudio::Play(char * audioSound)
{
	//audioSound = TEXT("audioSound");

	
	PlaySound(TEXT("../Assets/Sounds/RollingSpace.wav"), NULL, SND_LOOP | SND_ASYNC);
}
