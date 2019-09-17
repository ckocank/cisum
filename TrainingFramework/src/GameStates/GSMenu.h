#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "soloud.h"
#include "soloud_wav.h"

class GSMenu :
	public GameStateBase
{
public:
	GSMenu();
	~GSMenu();
	
	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	
	//void load(const char* filename);
	
private:
	std::shared_ptr<Sprite2D> m_BackGround, button1;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>  m_Text_gameName;
	//std::shared_ptr<SoLoud::Soloud> soloud;
	//std::shared_ptr<SoLoud::Wav> menusong;
	//SoLoud::Soloud soloud;

	static SoLoud::Soloud* soloud;
	SoLoud::Wav menusong, touch;


};

