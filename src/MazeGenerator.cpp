#include "MazeGenerator.h"
#include <ctime>

MazeGenerator::MazeGenerator(int xlength, int zlength):xlength(xlength), zlength(zlength){
	int i,x,z,temp;
	int n = xlength*zlength;
	unit = UNIT;
	Cell c;
	for(i=0; i<n; i++){
		s.push_back(-1);
		x = i%xlength+1;
		z = zlength-i/xlength-1;
		c.xcoord=x*unit;
		c.zcoord=z*unit;
		temp = i>=xlength*(zlength-1) ? 0 : 1;
		c.down=temp;
		temp = (i+1)%xlength==0 ? 0 : 1;
		c.right=temp;
		temp = z+1 == zlength ? 1 : 0;
		c.outerup = temp;
		temp = x == 1 ? 1 : 0;
		c.outerleft = temp;
		temp = x==xlength ? 1 : 0;
		c.outerright = temp;
		temp = z==0 ? 1 : 0;
		c.outerdown = temp;
		cells.push_back(c);
		visited.push_back(0);
	}
}


MazeGenerator::~MazeGenerator(void)
{
}

/*
precondition: n must be >= 0 and < s.size()
postcondition: return the root of n
*/
int MazeGenerator::find_root(int n){
	return s[n]<0 ? n : find_root(s[n]);
}
/*
precondition: root1 and root2 both must be >= 0 and < s.size()
postcondition: root1 and root2 belong to the same set
*/
void MazeGenerator::union_cell(int root1, int root2){
	s[find_root(root2)] = root1;
}

Maze* MazeGenerator::GenerateMaze(){
	int i, victim, neighbor, neighbor2;

/* initialize the random number generator */
	srand(time(0));   

/* push all elements into a vector except the last one because it has no walls to knock down */
	for(i=0; i<xlength*zlength-1; i++)
		lottery.push_back(i);
/* use a while loop to construct the maze */
	while(lottery.size()!=0){ 
		victim = lottery[rand()%lottery.size()];
/*victim has two neighbors*/
		if(cells[victim].down!=0 && cells[victim].right!=0){
			neighbor = victim+1;
			neighbor2 = victim+xlength;
/* if neither of them is joined, pick one and knock down the mutual wall */
			if(find_root(neighbor)!=find_root(victim) &&
				find_root(neighbor2)!=find_root(victim)){
				if(rand()%2==0){
					union_cell(victim, neighbor);
					cells[victim].right = -1;
				}
				else{
					union_cell(victim, neighbor2);
					cells[victim].down = -1;
				}
			}
/* if only one of them is joined, join another one and knock down the intersecting wall AND remove victim in vector lottery */
			else if(find_root(neighbor)!=find_root(victim)){
				union_cell(victim, neighbor);
				cells[victim].right = -1;
				remove(victim);
			}
			else if(find_root(neighbor2)!=find_root(victim)){
				union_cell(victim, neighbor2);
				cells[victim].down = -1;
				remove(victim);
			}
/* if both of them are joined, remove victim in vector lottery */
			else
				remove(victim);
			
		}
/*victim has one neighbor*/
		else{
/* determine which neighbor it is and if they are joined if not joined, join them and knock down the wall if joined, do nothing */
			if((victim+1)%xlength==0){
				neighbor = victim+xlength;
				if(find_root(neighbor)!=find_root(victim)){
					union_cell(victim, neighbor);
					cells[victim].down = -1;
				}
			}
			else{
				neighbor=victim+1;
				if(find_root(neighbor)!=find_root(victim)){
					union_cell(victim, neighbor);
					cells[victim].right = -1;
				}
			}
			remove(victim);
		}
	}
	if(cells.empty())
		return NULL;
	else
	{
		Maze* m_pMaze = new Maze(xlength, zlength, cells);
		return m_pMaze;
	}
}

/*
precondition: victim should, but not must, be an element in lottery
postcondition: victim is erased from lottery
*/
void MazeGenerator::remove(int victim){
	vector<int>::iterator vi;
	for(vi=lottery.begin(); vi!=lottery.end(); vi++)
		if(*vi==victim){
			lottery.erase(vi);
			return;
		}
}