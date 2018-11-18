#include "stdafx.h"
#include "Timer.h"
#include <iostream>

Timer::Timer(long incTime)
{
	interval = incTime;
}


Timer::~Timer()
{
}

void Timer::resetTimer()
{
	ticks = 0;
	realTicksBuffer = 0;
}

int Timer::startTimer()
{
	realTicksBuffer = getCurrentTime();
	while (true)
	{
		if (tickPass())
		{
			ticks++;
			if (mySimulator->proceed())
			{
				return ticks;
			}
		}
	}
}

bool Timer::tickPass()
{
	long nowTicksBuffer = getCurrentTime();
	if ((float)(nowTicksBuffer - realTicksBuffer) >= interval)
	{
		realTicksBuffer = getCurrentTime();
		return true;
	}
	else if (nowTicksBuffer < realTicksBuffer)
	{
		realTicksBuffer = getCurrentTime();
		return true;
	}
	return false;
}

void Timer::setSimulator(Simulator* mySim)
{
	mySimulator = mySim;
}

long Timer::getCurrentTime()
{
	SYSTEMTIME systime;
		GetSystemTime(&systime);
	return systime.wMilliseconds+ systime.wMinute*60*1000 + systime.wHour*60*60*1000+ systime.wDay * 60 * 60 * 1000*24;
	//return GetTickCount();
}
