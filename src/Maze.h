#pragma once
#include <vector>
#include "Wall.h"
#define UNIT 2
using namespace std;
struct Cell
{
	int xcoord;
	int zcoord;
	int down;
	int right;
	int outerup;
	int outerleft;
	int outerdown;
	int outerright;
};

class Maze
{
public:
	Maze(int xlength, int zlength, vector<Cell> cells);
	vector<Cell> GetCells();
	void SetCoords(double xcoord, double zcoord);
	int GetXCoord();
	int GetZCoord();
	int xlength;
	int zlength; 
	~Maze(void);
private:
	vector<Cell> cells;
	int xcoord;
	int zcoord;
};

