#pragma once
#include "MenuState.h"
#include "TextControl.h"
#include "Image.h"
class InstructionsState :
	public MenuState
{
public:
	static InstructionsState* GetInstance(StateManager* pStateManager);
protected:
	InstructionsState(StateManager* pStateManager);
	void Draw();
	void OnKeyDown(WPARAM wKey);
	~InstructionsState(void);
private:
	static InstructionsState* m_pInstructionsStateInstance;
	TImagePtr m_pTextImage;
};

