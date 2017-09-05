#pragma once
class Wall
{
public:
	Wall(int x1, int z1, int x2, int z2);
	bool CheckIntersection(double x, double z, double rad);
	~Wall(void);
private:
	int x1;
	int z1;
	int x2;
	int z2;
};

