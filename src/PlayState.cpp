#include "PlayState.h"
#include "StateManager.h"
#include "MainMenuState.h"
#include <Gl/glu.h>

PlayState* PlayState::m_pPlayStateInstance;

PlayState::PlayState(StateManager* pStateManager):GameState(pStateManager)
{
	bGameOver = false;
	bLockDirectionKeys = false;
	m_pMazeDrawer = NULL;
}

PlayState::~PlayState(void)
{
}

void PlayState::SetMaze(Maze* m_pMaze)
{
	this->m_pMazeDrawer = new MazeDrawer(m_pMaze);
	bGameOver = false;
}

PlayState* PlayState::GetInstance(StateManager* pStateManager)
{
	if(!m_pPlayStateInstance)
		m_pPlayStateInstance = new PlayState(pStateManager);
	return
		m_pPlayStateInstance;
}

bool PlayState::IsGameOver()
{
	return bGameOver;
}

void PlayState::Draw()
{
	m_pMazeDrawer->Draw();
}

void PlayState::OnKeyDown(WPARAM wKey)
{
	bool moveForward=false;
	bool moveBackward=false;
	float deltaAngle=0;
	float cameraRotationAngle=0;

	if(wKey == FORWARD_KEY && !bLockDirectionKeys)
		moveForward=true;
	if(wKey == BACKWARD_KEY && !bLockDirectionKeys)
		moveBackward=true;
	if(wKey == TURN_LEFT_KEY && !bLockDirectionKeys)
		deltaAngle -= 10.0;
	if(wKey == TURN_RIGHT_KEY && !bLockDirectionKeys)
		deltaAngle += 10.0;
	if(wKey == ROTATE_CAMERA_LEFT_KEY && !bLockDirectionKeys)
		cameraRotationAngle -= 0.1;
	if(wKey == ROTATE_CAMERA_RIGHT_KEY && !bLockDirectionKeys)
		cameraRotationAngle += 0.1;
	if(wKey == TOP_CAMERA_VIEW_KEY)
	{
		if(!bLockDirectionKeys)
		{
			bLockDirectionKeys = true;
		}
		else
		{
			bLockDirectionKeys = false;
		}
	}
	m_pMazeDrawer->Move(moveForward, moveBackward, deltaAngle, cameraRotationAngle, bLockDirectionKeys);

	if(wKey == VK_ESCAPE)
		ChangeState(MainMenuState::GetInstance(m_pStateManager));
	if(m_pMazeDrawer->GetHasWon())
	{
		bGameOver = true;
		ChangeState(MainMenuState::GetInstance(m_pStateManager));
	}
}

void PlayState::EnterState()
{
	//save the menu matrix
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)m_pStateManager->GetScreenWidth()/(double)m_pStateManager->GetScreenHeight(), 0.1, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.0);
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void PlayState::LeaveState()
{
	//restore the menu matrix
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, m_pStateManager->GetScreenWidth(), m_pStateManager->GetScreenHeight(), 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

void PlayState::SetProjection()
{
	gluPerspective(45.0, (double)m_pStateManager->GetScreenWidth()/(double)m_pStateManager->GetScreenHeight(), 0.1, 200.0);
}