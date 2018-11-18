#pragma once
#include "Simulator.h"
#include <windows.h>
class Timer
{
public:
	Timer(long incTime);
	~Timer();

	void resetTimer();
	int startTimer();
	void setSimulator(Simulator* mySim);
	int updateinterval(bool isAc)
	{
		if (!isAc)
		{
			if (interval < 1000)
			{
				interval += 10;
			}

		}
		else {
			if (interval > 20)
			{
				interval -= 10;
			}
		}
		return interval;
	}

private:
	//attribute
	int ticks;				//Time passed in Timer
	long realTicksBuffer;   //Last realtime recorded
	long interval;          //Interval : 1 (realwaord: simulation)-(second)
	Simulator* mySimulator;  //Binded simulator
	long getCurrentTime();  //Get millsecond is RealWorld

	//methods
	bool tickPass();        //busy waiting for reflash
};

