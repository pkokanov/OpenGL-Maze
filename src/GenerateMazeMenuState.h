#pragma once
#include "MenuState.h"
#include "Maze.h"

class GenerateMazeMenuState :
	public MenuState
{
public:
	GenerateMazeMenuState(StateManager* pStateManager);
	~GenerateMazeMenuState(void);
	static GenerateMazeMenuState* GetInstance(StateManager* pStateManager);
protected:
	void Draw();
	void OnKeyDown(WPARAM wKey);
	void EnterState();
	void SelectionUp();
	void SelectionDown();
	void SelectionChosen();
private:
	//function that calls the maze generator
	Maze* GenerateMaze();

	static GenerateMazeMenuState* m_pGenerateMazeMenuInstance;
	
	char m_pMazeWidth[3];
	char m_pMazeLenght[3];
	int m_iMazeLengthIndex;
	int m_iMazeWidthIndex;

	CTextControl* m_pGenerateMazeText;
	CTextControl* m_pMazeWidthText;
	CTextControl* m_pMazeLengthText;
	CTextControl* m_pBackText;
	CGameFont* m_pFontParameters;
	TImagePtr m_pMazeParamNotSelected;
	TImagePtr m_pMazeParamSelected;
};

