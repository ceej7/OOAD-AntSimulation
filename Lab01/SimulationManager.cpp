#include "stdafx.h"
#include "SimulationManager.h"
#include "Lab01View.h"


SimulationManager::SimulationManager(CView *view)
{
	pview = view;
	least = INT_MAX;
	most = 0;
}


SimulationManager::~SimulationManager()
{
}

void SimulationManager::caseInit()
{
	//30,80,110,160,250
	posCase.push_back(30);
	posCase.push_back(80);
	posCase.push_back(110);
	posCase.push_back(160);
	posCase.push_back(250);

	vector<bool> nullcase;
	generate_dir_by_number(nullcase, 0);
}

void SimulationManager::startSimulation()
{
	Timer timer(incTime);
	((CLab01View*)pview)->onFPSRefresh((int)(1000 / incTime));
	pTimer = &timer;
	for (size_t i = 0; i < dirCase.size(); i++)
	{	
		timer.resetTimer();
		Simulator sim(pview,i+1);
		sim.setSimCond(0, 300, 5, dirCase[i], posCase);
		bindTimerSim(timer, sim);
		int score=timer.startTimer();
		updateLeastMost(score);
	}
}

void SimulationManager::updateLeastMost(int ticks)
{
	if (ticks <= least)
	{
		least = ticks;
	}
	if (ticks >= most)
	{	
		most = ticks;
	}
	((CLab01View*)pview)->least = least;
	((CLab01View*)pview)->most = most;
}

void SimulationManager::generate_dir_by_number(vector<bool> mycase, int num)
{
	if (num < (posCase.size() - 1))
	{
		vector<bool> case1(mycase);
		case1.push_back(true);
		generate_dir_by_number(case1, num+1);
		
		vector<bool> case2(mycase);
		case2.push_back(false);
		generate_dir_by_number(case2, num+1);
	}
	else if (num == posCase.size() - 1)
	{
		vector<bool> case1(mycase);
		case1.push_back(true);
		dirCase.push_back(case1);

		vector<bool> case2(mycase);
		case2.push_back(false);
		dirCase.push_back(case2);
	}
}

void SimulationManager::bindTimerSim(Timer& timer, Simulator& sim)
{
	timer.setSimulator(&sim);
}

int SimulationManager::getLeast() {
	return least;
}

int SimulationManager::getMost()
{
	return most;
}

void SimulationManager::modifyRefreshingRate(bool isAc)
{
	int itv=pTimer->updateinterval(isAc);
	((CLab01View*)pview)->onFPSRefresh((int)(1000 / itv));
}