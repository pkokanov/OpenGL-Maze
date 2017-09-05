#include "NewGameMenuState.h"
#include "MainMenuState.h"
#include "GenerateMazeMenuState.h"
#include "PlayState.h"
#define GENERATE_MAZE 0
#define START_GAME 1
#define BACK 2

NewGameMenuState* NewGameMenuState::m_pNewGameMenuStateInstance;

NewGameMenuState::NewGameMenuState(StateManager* pStateManager):MenuState(pStateManager), 
	m_pMaze(NULL) 
{
	// Set the number of buttons in the menu
	m_buttons = 3;
	// Create the text controls of the menu
	m_pGenerateMazeText = new CTextControl(m_pFont,TRectanglei(150,207,209,591));
	m_pGenerateMazeText->SetAlignement(CTextControl::TACenter);
	m_pGenerateMazeText->SetText("Generate Maze");
	m_pStartGameText = new CTextControl(m_pFont,TRectanglei(250,307,209,591));
	m_pStartGameText->SetAlignement(CTextControl::TACenter);
	m_pStartGameText->SetText("Start Game");
	m_pBackText = new CTextControl(m_pFont,TRectanglei(350,407,209,591));
	m_pBackText->SetAlignement(CTextControl::TACenter);
	m_pBackText->SetText("Back");
}

NewGameMenuState::~NewGameMenuState(void){}

NewGameMenuState* NewGameMenuState::GetInstance(StateManager* pStateManager)
{
	if(!m_pNewGameMenuStateInstance)
		m_pNewGameMenuStateInstance = new NewGameMenuState(pStateManager);
	return
		m_pNewGameMenuStateInstance;
}

void NewGameMenuState::OnKeyDown(WPARAM wKey)
{
	switch(wKey)
	{
	case VK_DOWN:
		SelectionDown();
		break;
	case VK_UP:
		SelectionUp();
		break;
	case VK_RETURN:
		SelectionChosen();
		break;
	case VK_ESCAPE:
		ChangeState(MainMenuState::GetInstance(m_pStateManager));
		break;
	}
}

void NewGameMenuState::Draw()
{
	MenuState::Draw();
	m_pGenerateMazeText->Draw();
	m_pStartGameText->Draw();
	m_pBackText->Draw();
}

void NewGameMenuState::EnterState()
{
	m_iCurrentSelection=0;

	if(!m_pMaze)
		m_pStartGameText->SetTextColor(0.5,0.5,0.5);
	else
		m_pStartGameText->SetTextColor(1.0,1.0,1.0);
}

void NewGameMenuState::SelectionUp()
{
	m_iCurrentSelection--;
	if(m_iCurrentSelection<GENERATE_MAZE)
		m_iCurrentSelection=BACK;
	if(m_iCurrentSelection==START_GAME && !m_pMaze)
		m_iCurrentSelection--;
}

void NewGameMenuState::SelectionDown()
{
	m_iCurrentSelection++;
	if(m_iCurrentSelection>BACK)
		m_iCurrentSelection=GENERATE_MAZE;
	if(m_iCurrentSelection==START_GAME && !m_pMaze)
		m_iCurrentSelection++;
}

void NewGameMenuState::SelectionChosen()
{
	switch(m_iCurrentSelection)
	{
	case GENERATE_MAZE:
		ChangeState(GenerateMazeMenuState::GetInstance(m_pStateManager));
		break;
	case START_GAME:
		{
			PlayState* currentGame = PlayState::GetInstance(m_pStateManager);
			currentGame->SetMaze(m_pMaze);
			MainMenuState::GetInstance(m_pStateManager)->SetCurrentGame(currentGame);
			ChangeState(currentGame);
		}
		break;
	case BACK:
		ChangeState(MainMenuState::GetInstance(m_pStateManager));
		break;
	}
}

Maze* NewGameMenuState::GetMaze()
{
	return m_pMaze;
}

void NewGameMenuState::SetMaze(Maze* m_pMaze)
{
	this->m_pMaze=m_pMaze;
}