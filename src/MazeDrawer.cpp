#include "MazeDrawer.h"
#include "TextControl.h"
#include <math.h>
#include <iostream>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
using namespace std;

MazeDrawer::MazeDrawer(Maze* m_pMaze):m_pMaze(m_pMaze), deltax(0), deltaz(0), rotationAngle(0), cameraRotationAngle(0), up(false), hasWon(false)
{
	m_pModel = MD2Model::load("img\\tallguy.md2");
	if (m_pModel != NULL) {
		m_pModel->setAnimation("run");
	}
	currentCell = m_pMaze->GetCells()[0];
}


MazeDrawer::~MazeDrawer(void)
{
}

bool MazeDrawer::GetHasWon()
{
	return hasWon;
}

void MazeDrawer::Draw()
{
	std::vector<Cell> cells = m_pMaze->GetCells();
	int xlength = m_pMaze->xlength;
	int zlength = m_pMaze->zlength;
	GLfloat unit = UNIT;
	GLfloat xcoord = m_pMaze->GetXCoord();
	GLfloat zcoord = m_pMaze->GetZCoord();
	GLfloat initialXPos = xcoord + unit/2 - deltax;
	GLfloat initialYPos = unit*6;
	GLfloat initialZPos = zcoord - unit/2 - deltaz;
	GLfloat cameraXPos = initialXPos + sin(this->cameraRotationAngle);
	GLfloat cameraYPos = 0;
	GLfloat cameraZPos = initialZPos + cos(this->cameraRotationAngle);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(up)
		gluLookAt(initialXPos, initialYPos, initialZPos, initialXPos, 0, initialZPos, 0, 0, -1);
	else
		gluLookAt(cameraXPos, cameraYPos, cameraZPos , initialXPos, 0, initialZPos, 0, 1, 0);
	glPushMatrix();
	glTranslatef(initialXPos, 0.0f, initialZPos);
	GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix();
	if (m_pModel != NULL) {
		glPushMatrix();
		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
		glScalef(0.025f, 0.025f, 0.025f);
		glTranslatef(0.5f, -initialXPos/0.025f, -initialZPos/0.025f);
		glRotatef(rotationAngle, 1, 0, 0);
		m_pModel->draw();
		glPopMatrix();
	}
	//floor;
	glNormal3f(0.0f, 1.0f, 0.0f);
	DrawWall(xcoord, -0.5, zcoord - zlength*unit, xcoord + xlength*unit, -0.5, zcoord, initialXPos, initialZPos);
	//ceiling
	if(!up)
	{
		glNormal3f(0.0f, -1.0f, 0.0f);
		DrawWall(xcoord, 0.5, zcoord - zlength*unit, xcoord + xlength*unit, 0.5, zcoord, initialXPos, initialZPos);
	}
	//back wall
	glNormal3f(0.0f, 0.0f, -1.0f);
	DrawWall(xcoord, -0.5, zcoord, xcoord + xlength*unit, 0.5, zcoord, initialXPos, initialZPos);
	glNormal3f(0.0f, 1.0f, 0.0f);
	DrawWall(xcoord, 0.5, zcoord, xcoord + xlength*unit + 0.1, 0.5, zcoord + 0.2, initialXPos, initialZPos);
	//left wall
	glNormal3f(1.0f, 0.0f, 0.0f);
	DrawWall(xcoord, -0.5, zcoord - zlength*unit, xcoord, 0.5, zcoord, initialXPos, initialZPos);
	glNormal3f(0.0f, 1.0f, 0.0f);
	DrawWall(xcoord -0.2, 0.5, zcoord - zlength*unit - 0.2, xcoord, 0.5, zcoord + 0.2, initialXPos, initialZPos);
	for(unsigned int i = 0; i<cells.size(); i++)
	{
		if(cells[i].down==1 || cells[i].down==0)
		{
			glNormal3f(0.0f, 0.0f, 1.0f);
			DrawWall(cells[i].xcoord - unit - 0.1, -0.5, cells[i].zcoord + 0.1, cells[i].xcoord + 0.1, 0.5, cells[i].zcoord + 0.1, initialXPos, initialZPos);
			glNormal3f(0.0f, 0.0f, -1.0f);
			DrawWall(cells[i].xcoord - unit - 0.1, -0.5, cells[i].zcoord - 0.1, cells[i].xcoord + 0.1, 0.5, cells[i].zcoord - 0.1, initialXPos, initialZPos);
			glNormal3f(0.0f, 1.0f, 0.0f);
			DrawWall(cells[i].xcoord - unit - 0.1, 0.5, cells[i].zcoord - 0.1, cells[i].xcoord + 0.1, 0.5, cells[i].zcoord + 0.1, initialXPos, initialZPos);
			glNormal3f(1.0f, 0.0f, 0.0f);
			DrawWall(cells[i].xcoord + 0.1, -0.5, cells[i].zcoord - 0.1, cells[i].xcoord + 0.1, 0.5, cells[i].zcoord + 0.1, initialXPos, initialZPos);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			DrawWall(cells[i].xcoord - unit - 0.1, -0.5, cells[i].zcoord - 0.1, cells[i].xcoord - unit - 0.1, 0.5, cells[i].zcoord + 0.1, initialXPos, initialZPos);
		}

		if(cells[i].right==1 || cells[i].right==0)
		{
			glNormal3f(-1.0f, 0.0f, 0.0f);
			DrawWall(cells[i].xcoord - 0.1, -0.5, cells[i].zcoord, cells[i].xcoord - 0.1, 0.5, cells[i].zcoord + unit, initialXPos, initialZPos);
			glNormal3f(1.0f, 0.0f, 0.0f);
			DrawWall(cells[i].xcoord + 0.1, -0.5, cells[i].zcoord, cells[i].xcoord + 0.1, 0.5, cells[i].zcoord + unit, initialXPos, initialZPos);
			glNormal3f(0.0f, 1.0f, 0.0f);
			DrawWall(cells[i].xcoord - 0.1, 0.5, cells[i].zcoord, cells[i].xcoord + 0.1, 0.5, cells[i].zcoord + unit, initialXPos, initialZPos);
			glNormal3f(0.0f, 0.0f, -1.0f);
			DrawWall(cells[i].xcoord - 0.1, -0.5, cells[i].zcoord, cells[i].xcoord + 0.1, 0.5, cells[i].zcoord, initialXPos, initialZPos);
			glNormal3f(0.0f, 0.0f, 1.0f);
			DrawWall(cells[i].xcoord - 0.1, -0.5, cells[i].zcoord + unit, cells[i].xcoord + 0.1, 0.5, cells[i].zcoord + unit, initialXPos, initialZPos);
		}
	}
	DrawFinish(cells[cells.size()-1].xcoord,cells[cells.size()-1].zcoord, initialXPos, initialZPos);
}

void MazeDrawer::Move(bool moveForward, bool moveBackward, float rotationAngle, float cameraRotationAngle, bool up)
{
	float unit = UNIT;
	float f2 = -m_pMaze->GetXCoord() - unit/2.0;
	float f = m_pMaze->GetZCoord();
	this->rotationAngle+=rotationAngle;
	if(this->rotationAngle > 360.0) this->rotationAngle -= 360.0;
	if(this->rotationAngle < 0) this->rotationAngle += 360.0;
	this->up = up;
	this->cameraRotationAngle+=cameraRotationAngle;
	if(this->cameraRotationAngle <-360.0) this->cameraRotationAngle += 360.0;
	if(this->cameraRotationAngle > 360.0) this->cameraRotationAngle -= 360.0;

	if(moveForward)
	{
		if(!CheckCollision(moveForward))
		{
			this->deltax -= 0.05*sin(this->rotationAngle*(3.14/180));  
			this->deltaz += 0.05*cos(this->rotationAngle*(3.14/180)); 
		}
		if (m_pModel != NULL) {
			m_pModel->advance(0.10f, f2, f);
		}
	}
	if(moveBackward)
	{
		if(!CheckCollision(moveForward))
		{
			this->deltax += 0.05*sin(this->rotationAngle*(3.14/180));  
			this->deltaz -= 0.05*cos(this->rotationAngle*(3.14/180));
		}
		if (m_pModel != NULL) {
			m_pModel->advance(0.10f, f2, f);
		}
	}
}

bool MazeDrawer::CheckCollision(bool forward)
{
	bool result = false;
	int unit = UNIT;
	float posXAfterMove, posZAfterMove;
	float deltaXTest = 0, deltaZTest = 0;
	float xcoord = m_pMaze->GetXCoord();
	float zcoord = m_pMaze->GetZCoord();
	float initialXPos = xcoord + unit/2 - deltax;
	float initialZPos = zcoord - unit/2 - deltaz;
	if(forward)
	{
		deltaXTest -= 0.05*sin(this->rotationAngle*(3.14/180));  
		deltaZTest += 0.05*cos(this->rotationAngle*(3.14/180)); 
	}
	else
	{
		deltaXTest += 0.05*sin(this->rotationAngle*(3.14/180));  
		deltaZTest -= 0.05*cos(this->rotationAngle*(3.14/180));
	}
	posXAfterMove = initialXPos - deltaXTest;
	posZAfterMove = initialZPos - deltaZTest;
	int x = ceil(initialXPos/unit);
	int z = floor(initialZPos/unit);
	int cellNumbers[9];
	std::vector<Wall*> walls;

	//cellNumbers[0] is the current cell our guy is in
	cellNumbers[0] = GetAdjacentCellNumber(x, z);
	if(cellNumbers[0] == m_pMaze->xlength*m_pMaze->zlength - 1)
	{
		Cell cell = m_pMaze->GetCells()[cellNumbers[0]];
		if(initialXPos>cell.xcoord-1.25 && initialXPos<cell.xcoord-0.75 
			&& initialZPos > cell.zcoord+0.75 && initialZPos < cell.zcoord+1.25)
		{
			hasWon = true;
			return false;
		}
	}
	cellNumbers[1] = GetAdjacentCellNumber(x, z + 1);
	cellNumbers[2] = GetAdjacentCellNumber(x + 1, z);
	cellNumbers[3] = GetAdjacentCellNumber(x + 1, z+1);
	cellNumbers[4] = GetAdjacentCellNumber(x, z-1);
	cellNumbers[5] = GetAdjacentCellNumber(x-1, z);
	cellNumbers[6] = GetAdjacentCellNumber(x-1, z-1);
	cellNumbers[7] = GetAdjacentCellNumber(x+1, z-1);
	cellNumbers[8] = GetAdjacentCellNumber(x-1, z+1);
	for(int i=0; i<9; i++)
	{
		if(cellNumbers[i]!=-1)
		{
			Cell cell = m_pMaze->GetCells()[cellNumbers[i]];
			if(cell.down == 1 || cell.outerdown == 1)
				walls.push_back(new Wall(cell.xcoord, cell.zcoord, cell.xcoord - unit, cell.zcoord));
			if(cell.right == 1 || cell.outerright == 1)
				walls.push_back(new Wall(cell.xcoord, cell.zcoord, cell.xcoord, cell.zcoord + unit));
			if(cell.outerleft == 1)
				walls.push_back(new Wall(cell.xcoord - unit, cell.zcoord, cell.xcoord - unit, cell.zcoord + unit));
			if(cell.outerup == 1)
				walls.push_back(new Wall(cell.xcoord, cell.zcoord + unit, cell.xcoord - unit, cell.zcoord + unit));
		}
	}
	for(unsigned int i=0; i<walls.size(); i++)
	{
		result = result || walls[i]->CheckIntersection(posXAfterMove, posZAfterMove, (float)unit/15.0);
	}
	return result;
}

int MazeDrawer::GetAdjacentCellNumber(int x, int z)
{
	if(x<1 || x> m_pMaze->xlength || z<0 || z>m_pMaze->zlength-1)
		return -1;
	return (m_pMaze->zlength - z - 1) * m_pMaze->xlength + x-1;
}

void MazeDrawer::DrawWall(GLfloat x1, GLfloat y1
	, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat spriteXPos, GLfloat spriteZPos)
{
	glBegin(GL_QUADS);
	GLfloat mat_amb[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat mat_diff[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	float unit = 0.1;
	int viewDistance = 6;
	if(x1==x2 && x1>spriteXPos-viewDistance && x1<spriteXPos+viewDistance)
	{
		for(int i=y1*10; i<y2*10; i++)
		{
			for(int j=(int)((spriteZPos-viewDistance>=z1 ? spriteZPos-viewDistance : z1)*10 + 0.5); j<(int)((z2>=spriteZPos+viewDistance ? spriteZPos+viewDistance : z2)*10 + 0.5); j++)
			{
				glVertex3f(x1, i/10.0, j/10.0);
				glVertex3f(x1, i/10.0, j/10.0 + unit);
				glVertex3f(x1, i/10.0 + unit, j/10.0 + unit);
				glVertex3f(x1, i/10.0 + unit, j/10.0);
			}
		}
	}
	else if(y1==y2)
	{
		for(int i=(int)((spriteXPos-viewDistance>=x1 ? spriteXPos-viewDistance : x1)*10 + 0.5); i<(int)((x2>=spriteXPos+viewDistance ? spriteXPos+viewDistance : x2)*10 + 0.5); i++)
		{
			for(int j=(int)((spriteZPos-viewDistance>=z1 ? spriteZPos-viewDistance : z1)*10 + 0.5); j<(int)((z2>=spriteZPos+viewDistance ? spriteZPos+viewDistance : z2)*10 + 0.5); j++)
			{
				glVertex3f(i/10.0, y1, j/10.0);
				glVertex3f(i/10.0, y1, j/10.0 + unit);
				glVertex3f(i/10.0 + unit, y1, j/10.0 + unit);
				glVertex3f(i/10.0 + unit, y1, j/10.0);
			}
		}
	}
	else if(z1==z2 && z1>spriteZPos-viewDistance && z1<spriteZPos+viewDistance)
	{
		for(int i=(int)((spriteXPos-viewDistance>=x1 ? spriteXPos-viewDistance : x1)*10 + 0.5); i<(int)((x2>=spriteXPos+viewDistance ? spriteXPos+viewDistance : x2)*10 + 0.5); i++)
		{
			for(int j=y1*10; j<y2*10; j++)
			{
				glVertex3f(i/10.0, j/10.0, z1);
				glVertex3f(i/10.0, j/10.0 + unit, z1);
				glVertex3f(i/10.0 + unit, j/10.0 + unit, z1);
				glVertex3f(i/10.0 + unit, j/10.0, z1);
			}
		}
	}
	glEnd();
}

void MazeDrawer::DrawFinish(int x, int z, float spriteXPos, float spriteZPos)
{
	int viewDistance = 8;
	if(x>spriteXPos+viewDistance || z<spriteZPos-viewDistance)
		return;
	glPushMatrix();
	glTranslatef(x - (float)UNIT/2, 0.0f, z + (float)UNIT/2);
	glBegin(GL_QUADS);
	GLfloat dif_mat[] = {0.1, 0.7, 0.1, 1.0};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif_mat);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(0.25, -0.5, 0.25);
	glVertex3f(0.25,  0.25, 0.25);
	glVertex3f(-0.25,  0.25, 0.25);
	glVertex3f(-0.25, -0.5, 0.25);

	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(0.25, -0.5, -0.25);
	glVertex3f(0.25,  0.25, -0.25);
	glVertex3f(0.25,  0.25,  0.25);
	glVertex3f(0.25, -0.5,  0.25);

	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-0.25, -0.5,  0.25);
	glVertex3f(-0.25,  0.25,  0.25);
	glVertex3f(-0.25,  0.25, -0.25);
	glVertex3f(-0.25, -0.5, -0.25);

	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(0.25,  0.25,  -0.25);
	glVertex3f(0.25,  -0.5, -0.25);
	glVertex3f(-0.25, -0.5, -0.25);
	glVertex3f(-0.25,  0.25,  -0.25 );

	glVertex3f(0.25,  0.25,  0.25);
	glVertex3f(0.25,  0.25, -0.25);
	glVertex3f(-0.25,  0.25, -0.25);
	glVertex3f(-0.25,  0.25,  0.25 );

	glVertex3f(0.25, -0.5, -0.25);
	glVertex3f( 0.25, -0.5,  0.25);
	glVertex3f(-0.25, -0.5,  0.25);
	glVertex3f(-0.25, -0.5, -0.25);
	glEnd();
	glPopMatrix();
}