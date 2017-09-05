#include "StateManager.h"

StateManager::StateManager(void):m_pActiveState(NULL){}

StateManager::~StateManager(void){}

void StateManager::ChangeState(GameState* pNewState)
{
	if (m_pActiveState)
		m_pActiveState->LeaveState();
	m_pActiveState = pNewState;
	m_pActiveState->EnterState();
}

void StateManager::Draw()
{
	if (m_pActiveState)
		m_pActiveState->Draw();
}

void StateManager::Update(DWORD dwCurrentTime)
{
	if (m_pActiveState)
		m_pActiveState->Update(dwCurrentTime);
}

GameState* StateManager::GetActiveState()
{
	return m_pActiveState;
}

void StateManager::OnKeyDown(WPARAM wKey)
{
	if(m_pActiveState)
		m_pActiveState->OnKeyDown(wKey);
}

void StateManager::OnKeyUp(WPARAM wKey)
{
	if(m_pActiveState)
		m_pActiveState->OnKeyUp(wKey);
}

void StateManager::SetScreenSize(GLsizei width, GLsizei height)
{
	this->screenHeight = height;
	this->screenWidth = width;
}

GLsizei StateManager::GetScreenHeight()
{
	return screenHeight;
}

GLsizei StateManager::GetScreenWidth()
{
	return screenWidth;
}