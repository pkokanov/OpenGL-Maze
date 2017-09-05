#pragma once
#include "GameState.h"
#include "Maze.h"
#include "MazeDrawer.h"

#define FORWARD_KEY 87 //w
#define BACKWARD_KEY 83 //s
#define TURN_LEFT_KEY 65 //a
#define TURN_RIGHT_KEY 68//d
#define ROTATE_CAMERA_LEFT_KEY VK_LEFT//<-
#define ROTATE_CAMERA_RIGHT_KEY VK_RIGHT//-> 
#define TOP_CAMERA_VIEW_KEY 80 //p
#define SPEED 0.2

class PlayState :
	public GameState
{
public:
	bool IsGameOver();
	static PlayState* GetInstance(StateManager* pStateManager);
	void SetMaze(Maze* m_pMaze);
	void SetProjection();
protected:
	PlayState(StateManager* pStateManager);
	void OnKeyDown(WPARAM wKey);
	//void Update(DWORD dwCurrentTime);
	void Draw();
	//Functions called when the state transitions from one to another.
	void EnterState();
	void LeaveState();
	~PlayState(void);
private:
	static PlayState* m_pPlayStateInstance;
	bool bGameOver;
	bool bLockDirectionKeys;
	MazeDrawer* m_pMazeDrawer;
};

