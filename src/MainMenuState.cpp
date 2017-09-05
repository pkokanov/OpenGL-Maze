#include "MainMenuState.h"
#include "InstructionsState.h"
#include "StateManager.h"
#include "NewGameMenuState.h"

#define NEW_GAME 0
#define RESUME 1
#define INSTRUCTIONS 2
#define QUIT 3

MainMenuState* MainMenuState::m_pMainMenuStateInstance = NULL;

MainMenuState::MainMenuState(StateManager* pStateManager):MenuState(pStateManager),
	m_pCurrentGame(NULL)
{
	// Set the number of buttons in the menu
	m_buttons = 4;
	// Create the text controls of the menu.
	m_pNewGameText = new CTextControl(m_pFont,TRectanglei(150,207,209,591));
	m_pNewGameText->SetAlignement(CTextControl::TACenter);
	m_pNewGameText->SetText("New game");
	m_pResumeGameText = new CTextControl(m_pFont,TRectanglei(250,307,209,591));
	m_pResumeGameText->SetAlignement(CTextControl::TACenter);
	m_pResumeGameText->SetText("Resume game");
	m_pScoresText = new CTextControl(m_pFont,TRectanglei(350,407,209,591));
	m_pScoresText->SetAlignement(CTextControl::TACenter);
	m_pScoresText->SetText("How To Play");
	m_pExitText = new CTextControl(m_pFont,TRectanglei(450,507,209,591));
	m_pExitText->SetAlignement(CTextControl::TACenter);
	m_pExitText->SetText("Exit");
}

MainMenuState::~MainMenuState(void){}

MainMenuState* MainMenuState::GetInstance(StateManager* pStateManager)
{
	if(!m_pMainMenuStateInstance)
		m_pMainMenuStateInstance = new MainMenuState(pStateManager);
	return m_pMainMenuStateInstance;
}

void MainMenuState::Draw()
{
	MenuState::Draw();
	m_pNewGameText->Draw();
	m_pResumeGameText->Draw();
	m_pScoresText->Draw();
	m_pExitText->Draw();
}

void MainMenuState::OnKeyDown(WPARAM wKey)
{
	switch (wKey)
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
		PostQuitMessage(0);
		break;
	}
}

void MainMenuState::EnterState()
{
	m_iCurrentSelection = 0;
	if (!m_pCurrentGame || m_pCurrentGame->IsGameOver())
		m_pResumeGameText->SetTextColor(0.5,0.5,0.5);
	else
		m_pResumeGameText->SetTextColor(1.0,1.0,1.0);
}

void MainMenuState::SelectionDown()
{
	m_iCurrentSelection++;
	if (m_iCurrentSelection>QUIT)
		m_iCurrentSelection = NEW_GAME;

	// If there is no current game, we should skip
	// the "Resume game" item.
	if (m_iCurrentSelection==RESUME) 
	{
		if (!m_pCurrentGame || m_pCurrentGame->IsGameOver())
			m_iCurrentSelection++;
	}
}

void MainMenuState::SelectionUp()
{
	m_iCurrentSelection--;
	if (m_iCurrentSelection<NEW_GAME)
		m_iCurrentSelection = QUIT;

	// If there is no current game, we should skip
	// the "Resume game" item.
	if (m_iCurrentSelection==RESUME) 
	{
		if (!m_pCurrentGame || m_pCurrentGame->IsGameOver())
			m_iCurrentSelection--;
	}
}

void MainMenuState::SelectionChosen()
{
	switch(m_iCurrentSelection)
	{
	case(NEW_GAME):
		ChangeState(NewGameMenuState::GetInstance(m_pStateManager));
		break;
	case(RESUME):
		ChangeState(m_pCurrentGame);
		break;
	case(INSTRUCTIONS):
		ChangeState(InstructionsState::GetInstance(m_pStateManager));
		break;
	case(QUIT):
		PostQuitMessage(0);
		break;
	}
}

void MainMenuState::SetCurrentGame(PlayState* m_pCurrentGame)
{
	this->m_pCurrentGame = m_pCurrentGame;
}