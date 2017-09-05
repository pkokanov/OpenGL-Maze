#pragma once
#include "Maze.h"

using namespace std;

class MazeGenerator
{
public:
	MazeGenerator(int xlength, int zlength);
	Maze* GenerateMaze();
	~MazeGenerator(void);
private:
	int find_root(int);	
	void union_cell(int, int);
	void remove(int);
	vector<Cell> cells;
	vector<int> s;  /* parent\'s id */
	vector<int> visited;  /* 1 means visited and 0 means not visited yet while finding solution */
	vector<int> lottery;
	int unit;
	int xlength, zlength, numOfCells;
};

