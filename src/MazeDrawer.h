#pragma once
#include "Maze.h"
#include "MD2Model.h"
#include "Image.h"

class MazeDrawer
{
public:
	MazeDrawer(Maze* m_pMaze);
	void Draw();
	void Move(bool moveForward, bool moveBackward, float rotationAngle, float cameraRotationAngle, bool up);
	bool GetHasWon();
	~MazeDrawer(void);
private:
	bool CheckCollision(bool forward);
	void DrawWall(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat spriteXPos, GLfloat spriteZPos);
	int GetAdjacentCellNumber(int x, int z);
	void DrawFinish(int x, int z, float spriteXPos, float spriteZPos);
	Maze* m_pMaze;
	GLfloat deltax;
	GLfloat deltaz;
	GLfloat rotationAngle;
	GLfloat cameraRotationAngle;
	Cell currentCell;
	bool hasWon;
	bool up;
	MD2Model* m_pModel;
};

