#include "PlayState.h"
#include "MenuState.h"

class MainMenuState :
	public MenuState
{
protected:
	MainMenuState(StateManager* pStateManager);
	~MainMenuState(void);
public:
	static MainMenuState* GetInstance(StateManager* pStateManager);
	void SetCurrentGame(PlayState* m_pCurrentGame);
	// Methods inherited from GameState class.
	void OnKeyDown(WPARAM wKey);
	void Draw();
	void EnterState();
	void SelectionUp();
	void SelectionDown();
	void SelectionChosen();
private:
	static MainMenuState* m_pMainMenuStateInstance;

	// A pointer to the current active game (if any).
	PlayState* m_pCurrentGame;

	// The text controls of the different entries.
	CTextControl* m_pNewGameText;
	CTextControl* m_pResumeGameText;
	CTextControl* m_pScoresText;
	CTextControl* m_pExitText;
};

