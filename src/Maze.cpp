#include "Maze.h"

Maze::Maze(int xlength, int zlength, vector<Cell> cells): xlength(xlength), zlength(zlength), cells(cells)
{
	this->xcoord=cells[0].xcoord - UNIT;
	this->zcoord=cells[0].zcoord + UNIT;
}

std::vector<Cell> Maze::GetCells()
{
	return this->cells;
}

int Maze::GetXCoord()
{
	return xcoord;
}

int Maze::GetZCoord()
{
	return zcoord;
}
Maze::~Maze(void)
{
}
