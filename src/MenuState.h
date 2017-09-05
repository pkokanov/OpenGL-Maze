#pragma once
#include "GameState.h"
#include "GameFont.h"
#include "TextControl.h"
#include "Image.h"

class MenuState :
	public GameState
{
public:
	MenuState(StateManager* pStateManager);
	~MenuState(void);
	void SetProjection();
protected:
	// Methods inherited from GameState class.
	void Draw();
	// Functions that must be realised by children menus
	// Player choices: UP or DOWN
	virtual void SelectionUp();
	virtual void SelectionDown();
	// The player chooses a selection
	virtual void SelectionChosen();
	
	// Index of the current selected menu item
	int m_iCurrentSelection;

	// Number of buttons in the menu
	int m_buttons;

	CGameFont* m_pFont;
	// The background image
	TImagePtr m_pBackgroundImg;

	// The images of the menu items (normal and
	// selected).
	TImagePtr m_pItemBckgndNormal;
	TImagePtr m_pItemBckgndSelected;
};

