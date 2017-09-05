#include "Wall.h"
#include <math.h>

Wall::Wall(int x1, int z1, int x2, int z2):x1(x1), x2(x2), z1(z1), z2(z2)
{
}


Wall::~Wall(void)
{
}

bool Wall::CheckIntersection(double x, double z, double rad)
{
	if(x1==x2 && abs(x1-x)<=rad && (z2>z1 && z<=z2+rad && z>=z1-rad || z1>z2 && z<=z1+rad && z>=z2-rad))
		return true;
	else if(z1==z2 && abs(z1-z)<=rad && (x2>x1 && x<=x2+rad && x>=x1-rad || x1>x2 && x<=x1+rad && x>=x2-rad))
		return true;
	else 
		return false;
}
