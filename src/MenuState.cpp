#include "MenuState.h"
#include "StateManager.h"
MenuState::MenuState(StateManager* pStateManager):GameState(pStateManager),
	m_pFont(NULL), m_iCurrentSelection(0)
{
	m_pFont = new CGameFont;
	m_pFont->CreateFont("Verdana", 30, FW_NORMAL);

	// Create the different images
	m_pBackgroundImg = CImage::CreateImage("img\\MainBackground.png",TRectanglei(0,600,0,800));
	m_pItemBckgndNormal = CImage::CreateImage("img\\MenuItems.png",TRectanglei(0,57,0,382));
	m_pItemBckgndSelected = CImage::CreateImage("img\\MenuItems.png",TRectanglei(58,114,0,382));
}

MenuState::~MenuState(void){}

void MenuState::Draw()
{
	m_pBackgroundImg->BlitImage();
	// Draw the menu item backgrounds
	for (int i=0;i<m_buttons;i++)
	{
		if (i==m_iCurrentSelection)
			m_pItemBckgndSelected->BlitImage(209,150+i*100);
		else
			m_pItemBckgndNormal->BlitImage(209,150+i*100);
	}
	
}

void MenuState::SetProjection()
{
	glOrtho(0.0, m_pStateManager->GetScreenWidth(), m_pStateManager->GetScreenHeight(), 0.0, -1.0, 1.0);
}
void MenuState::SelectionUp(){}

void MenuState::SelectionDown(){}

void MenuState::SelectionChosen(){}