#include "InstructionsState.h"
#include "MainMenuState.h"

InstructionsState* InstructionsState::m_pInstructionsStateInstance = NULL;

InstructionsState::InstructionsState(StateManager* pStateManager):MenuState(pStateManager)
{
	m_buttons = 0;
	m_pTextImage = CImage::CreateImage("img\\Instructions.png", TRectanglei(0,500,0,700));
}


InstructionsState::~InstructionsState(void)
{
}

InstructionsState* InstructionsState::GetInstance(StateManager* m_pStateManager)
{
	if(!m_pInstructionsStateInstance)
		m_pInstructionsStateInstance = new InstructionsState(m_pStateManager);
	return m_pInstructionsStateInstance;
}

void InstructionsState::Draw()
{
	MenuState::Draw();
	m_pTextImage->BlitImage(50, 60);
}

void InstructionsState::OnKeyDown(WPARAM wKey)
{
	ChangeState(MainMenuState::GetInstance(m_pStateManager));
}
