#include "GameState.h"
#include "StateManager.h"
GameState::GameState(StateManager* pStateManager):m_pStateManager(pStateManager){}

GameState::~GameState(void){}

void GameState::ChangeState(GameState* pNewState)
{
	m_pStateManager->ChangeState(pNewState);
}

void GameState::Draw(){}

void GameState::Update(DWORD dwCurrentTime){}

void GameState::OnKeyDown(WPARAM wKey){}

void GameState::OnKeyUp(WPARAM wKey){}

void GameState::EnterState(){}

void GameState::LeaveState(){}

void GameState::SetProjection(){}