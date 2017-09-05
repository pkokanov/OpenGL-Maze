#include "GenerateMazeMenuState.h"
#include "NewGameMenuState.h"
#include "MazeGenerator.h"

#define MAZE_LENGHT 0
#define MAZE_WIDTH 1
#define GENERATE_MAZE 2
#define BACK 3

GenerateMazeMenuState* GenerateMazeMenuState::m_pGenerateMazeMenuInstance = NULL;

GenerateMazeMenuState::GenerateMazeMenuState(StateManager* pStateManager):MenuState(pStateManager),
	m_iMazeLengthIndex(0), m_iMazeWidthIndex(0)
{
	//Set the number of buttons
	m_buttons = 4;
	// Create the text controls of the menu
	m_pFontParameters = new CGameFont;
	m_pFontParameters->CreateFont("Verdana", 30, FW_NORMAL);
	m_pMazeLenght[0]='\0';
	m_pMazeWidth[0]='\0';
	m_pMazeParamNotSelected = CImage::CreateImage("img\\WidthLength.png", TRectanglei(0, 52, 0, 64));
	m_pMazeParamSelected = CImage::CreateImage("img\\WidthLength.png", TRectanglei(52, 103, 0, 64));
	m_pMazeLengthText = new CTextControl(m_pFont, TRectanglei(150, 207, 159, 541));
	m_pMazeLengthText->SetAlignement(CTextControl::TACenter);
	m_pMazeLengthText->SetText("Maze Length:");
	m_pMazeLengthText->SetTextColor(0.0, 0.0, 0.0);
	m_pMazeWidthText = new CTextControl(m_pFont, TRectanglei(250, 307, 159, 541));
	m_pMazeWidthText->SetAlignement(CTextControl::TACenter);
	m_pMazeWidthText->SetText("Maze Width:");
	m_pMazeWidthText->SetTextColor(0.0, 0.0, 0.0);
	m_pGenerateMazeText = new CTextControl(m_pFont,TRectanglei(350,407,209,591));
	m_pGenerateMazeText->SetAlignement(CTextControl::TACenter);
	m_pGenerateMazeText->SetText("Generate Maze");
	m_pBackText = new CTextControl(m_pFont,TRectanglei(450,507,209,591));
	m_pBackText->SetAlignement(CTextControl::TACenter);
	m_pBackText->SetText("Back");

}

GenerateMazeMenuState::~GenerateMazeMenuState(void){}

GenerateMazeMenuState* GenerateMazeMenuState::GetInstance(StateManager *pStateManager)
{
	if(!m_pGenerateMazeMenuInstance)
		m_pGenerateMazeMenuInstance = new GenerateMazeMenuState(pStateManager);
	return m_pGenerateMazeMenuInstance;
}

void GenerateMazeMenuState::Draw()
{
	m_pBackgroundImg->BlitImage();
	for(int i=0;i<m_buttons;i++)
	{
		if(i<2&&i==m_iCurrentSelection)
		{
			m_pMazeParamSelected->BlitImage(510, 150+i*100);
		}
		else if(i<2)
		{
			m_pMazeParamNotSelected->BlitImage(510, 150+i*100);
		}
		else if(i>=2&&i==m_iCurrentSelection)
		{
			m_pItemBckgndSelected->BlitImage(209, 150+i*100);
		}
		else if(i>=2)
		{
			m_pItemBckgndNormal->BlitImage(209, 150+i*100);
		}
	}
	m_pFontParameters->DrawTextA(m_pMazeLenght, 520, 185, 1.0, 1.0, 1.0);
	m_pFontParameters->DrawTextA(m_pMazeWidth, 520, 285, 1.0, 1.0, 1.0);
	m_pGenerateMazeText->Draw();
	m_pBackText->Draw();
	m_pMazeWidthText->Draw();
	m_pMazeLengthText->Draw();
}

void GenerateMazeMenuState::EnterState()
{
	m_iCurrentSelection = MAZE_LENGHT;
}

void GenerateMazeMenuState::OnKeyDown(WPARAM wKey)
{
	if(m_iCurrentSelection == MAZE_LENGHT)
	{
		if(wKey==VK_BACK&&m_iMazeLengthIndex>0)
		{	
			m_iMazeLengthIndex--;
			m_pMazeLenght[m_iMazeLengthIndex]='\0';
		}
		else if(wKey==VK_TAB)
		{
			SelectionDown();
		}
		else if(wKey>47 && wKey<58 && m_iMazeLengthIndex<2)
		{
			m_pMazeLenght[m_iMazeLengthIndex++]=wKey;
			m_pMazeLenght[m_iMazeLengthIndex]='\0';
		}			
	}
	else if(m_iCurrentSelection==MAZE_WIDTH)
	{
		if(wKey==VK_BACK&&m_iMazeWidthIndex>0)
		{	
			m_iMazeWidthIndex--;
			m_pMazeWidth[m_iMazeWidthIndex]='\0';
		}
		else if(wKey==VK_TAB)
		{
			SelectionDown();
		}
		else if(wKey>47 && wKey<58 && m_iMazeWidthIndex<2)
		{
			m_pMazeWidth[m_iMazeWidthIndex++]=wKey;
			m_pMazeWidth[m_iMazeWidthIndex]='\0';
		}	
	}

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
		ChangeState(NewGameMenuState::GetInstance(m_pStateManager));
		break;
	}
}

void GenerateMazeMenuState::SelectionUp()
{
	m_iCurrentSelection--;
	if(m_iCurrentSelection<MAZE_LENGHT)
		m_iCurrentSelection=BACK;
}

void GenerateMazeMenuState::SelectionDown()
{
	m_iCurrentSelection++;
	if(m_iCurrentSelection>BACK)
		m_iCurrentSelection=MAZE_LENGHT;
}

void GenerateMazeMenuState::SelectionChosen()
{
	if(m_iCurrentSelection==GENERATE_MAZE)
	{
		Maze* m_pMaze = GenerateMaze();
		NewGameMenuState::GetInstance(m_pStateManager)->SetMaze(m_pMaze);
		if(m_pMaze)
			ChangeState(NewGameMenuState::GetInstance(m_pStateManager));
	}
	else if(m_iCurrentSelection==BACK)
	{
		ChangeState(NewGameMenuState::GetInstance(m_pStateManager));
	}
}

Maze* GenerateMazeMenuState::GenerateMaze()
{
	int width=0;
	int length=0;
	if(m_pMazeLenght[0]!='\0')
	{
		length = atoi(m_pMazeLenght);
	}
	if(m_pMazeWidth[0]!='\0')
	{
		width = atoi(m_pMazeWidth);
	}
	if(length==0||width==0)
		return NULL;
	else
	{
		MazeGenerator* m_pMazeGenerator = new MazeGenerator(length, width);
		return m_pMazeGenerator->GenerateMaze();
	}
}