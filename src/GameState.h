#pragma once
#include <Windows.h>
#include <gl\GL.h>

class StateManager;
class GameState
{
public:
	GameState(StateManager* pStateManager);
	virtual ~GameState(void);
	void ChangeState(GameState* pNewState);
	//'Events' functions. Child classes should implement the ones they need.
	virtual void OnKeyUp(WPARAM wKey);
	virtual void OnKeyDown(WPARAM wKey);
	virtual void Update(DWORD dwCurrentTime);
	virtual void Draw();
	virtual void SetProjection();
	//Functions called when the state transitions from one to another.
	virtual void EnterState();
	virtual void LeaveState();
protected:
	StateManager* m_pStateManager;
};

