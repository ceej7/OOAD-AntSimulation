#pragma once
class Ant
{
public:
	Ant(int pos, bool dir, int v, int number);
	~Ant();

	//Modify state
	void crawl(int sec);
	void die();
	void turnBack();

	//Query state
	int getPos();
	bool getDir();
	bool isDie();

	int no=0;
private:
	int position;
	bool direction;//true is left, false is right
	int velocity;
	bool isDead;


};

