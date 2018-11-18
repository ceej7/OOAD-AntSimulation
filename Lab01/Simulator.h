#pragma once
#include "Ant.h"
#include <vector>
using namespace::std;
class CView;
class Simulator
{
public:
	Simulator(CView *view,int num);
	~Simulator();

	//method
	void setSimCond(int left,int right,int num,vector<bool> dirs, vector<int> pos); //Initialing
	bool proceed();//Proceed in one tick
	
private:
	//attributes
	vector<Ant> ants;	
	int leftMost; //pole's left end
	int rightMost;//pole's right end
	CView *pview;
	int roundNumber;

	//methods
	void decideDrop();       //Determine any ant dropped and send messages
	void decideCollision();  //Determine any ant collided and send messages
	bool isAllDropped();     //Simulation terminating detection
};

