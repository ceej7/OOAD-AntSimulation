#include "stdafx.h"
#include "Simulator.h"
#include "Lab01View.h"

Simulator::Simulator(CView *view, int num)
{
	pview = view;
	roundNumber = num;
}


Simulator::~Simulator()
{

}

bool Simulator::proceed()
{
	for (size_t i = 0; i < ants.size(); i++)
	{
		ants[i].crawl(1);
	}
	decideDrop();
	decideCollision();
	((CLab01View*)pview)->onDrawDataRefresh(leftMost, rightMost, ants,roundNumber);
	return isAllDropped();
}

void Simulator::decideDrop()
{
	for (size_t i = 0; i < ants.size(); i++)
	{
		if(!ants[i].isDie())
			if ((ants[i].getPos() <= leftMost&& ants[i].getDir()==true) || (ants[i].getPos() >= rightMost&& ants[i].getDir() == false))
			{
				ants[i].die();
			}
	}
}

void Simulator::decideCollision()
{
	for (size_t i = 0; i < ants.size(); i++)
	{
		if (!ants[i].isDie())
		{
			for (size_t j = i + 1; j < ants.size(); j++)
			{
				if (!ants[j].isDie())
				{
					if (ants[i].getPos() == ants[j].getPos())
					{
						ants[i].turnBack();
						ants[j].turnBack();
					}
				}
			}
		}
	}

}

bool Simulator::isAllDropped()
{
	for (size_t i = 0; i < ants.size(); i++)
	{
		if (ants[i].isDie() == false)
			return false;
	}
	return true;
}

void Simulator::setSimCond(int left, int right, int num, vector<bool> dirs, vector<int> pos)
{
	leftMost = left;
	rightMost = right;

	for (int i = 0; i < num; i++)
	{
		Ant ant(pos[i],dirs[i],5,i+1);
		ants.push_back(ant);
	}
}