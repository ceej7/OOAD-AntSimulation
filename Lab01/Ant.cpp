#include "stdafx.h"
#include "Ant.h"


Ant::Ant(int pos, bool dir, int v,int number)
{
	position = pos;
	direction = dir;
	velocity = v;
	isDead = false;
	no = number;
}


Ant::~Ant()
{
}

void Ant::crawl(int sec)
{
	if (isDie())
		return;
	int coef = direction ? -1 : 1;
	position = position + coef * sec*velocity;
}
void Ant::die()
{
	isDead = true;
}
void Ant::turnBack()
{
	direction = !direction;
}

int Ant::getPos()
{
	return position;
}
bool Ant::getDir()
{
	return direction;
}

bool Ant::isDie()
{
	return isDead;
}