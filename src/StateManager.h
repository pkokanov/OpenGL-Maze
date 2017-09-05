#pragma once
#include "GameState.h"

class StateManager
{
	//TODO: think about making this a singleton class
public:
	void ChangeState(GameState* pNewState);
	GameState* GetActiveState();
	void SetScreenSize(GLsizei width, GLsizei height);
	GLsizei GetScreenWidth();
	GLsizei GetScreenHeight();
	// 'Events' function, they are simply redirected to
	// the active state.
	void OnKeyDown(WPARAM wKey);
	void OnKeyUp(WPARAM wKey);
	void Update(DWORD dwCurrentTime);
	void Draw();
	StateManager(void);
	~StateManager(void);
private:
	// Active State of the game
	GameState* m_pActiveState;
	GLsizei screenWidth;
	GLsizei screenHeight;
};

