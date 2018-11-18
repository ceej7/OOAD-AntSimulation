#pragma once
#include <vector>
#include "Simulator.h"
#include "Timer.h"
using namespace::std;

const long incTime = 60;
class CView;
class SimulationManager
{
public:
//method
	//Con&Destructor
	SimulationManager(CView *view);
	~SimulationManager();

	
	void caseInit();//Generate ants's direction and position
	void startSimulation();//Command to start all simulation
	int getLeast();
	int getMost();
	void modifyRefreshingRate(bool isAc);

//attribute
	

private:
//method
	void generate_dir_by_number(vector<bool> mycase, int num);//Recursively traverse all posibility
	void updateLeastMost(int ticks);
	void bindTimerSim(Timer& timer, Simulator& sim);

//attribute
	vector<vector<bool>> dirCase;
	vector<int> posCase;
	int least, most;
	CView *pview;
	Timer *pTimer;
	
};


