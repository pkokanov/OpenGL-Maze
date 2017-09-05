#pragma once
#include "MenuState.h"
#include "Maze.h"

class NewGameMenuState :
	public MenuState
{
public:
	static NewGameMenuState* GetInstance(StateManager* pStateManager);
	Maze* GetMaze();
	void SetMaze(Maze* m_pMaze);
protected:
	NewGameMenuState(StateManager* pStateManager);
	~NewGameMenuState(void);
	void OnKeyDown(WPARAM wKey);
	void Draw();
	void EnterState();
	void SelectionUp();
	void SelectionDown();
	void SelectionChosen();
private:
	static NewGameMenuState* m_pNewGameMenuStateInstance;
	// Pointer to the generated maze
	Maze* m_pMaze;

	CTextControl* m_pGenerateMazeText;
	CTextControl* m_pStartGameText;
	CTextControl* m_pBackText;
};

