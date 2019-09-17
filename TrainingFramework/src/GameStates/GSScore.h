#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "soloud.h"
#include "soloud_wav.h"

class Sprite2D;
class Sprite3D;
class Text;

class GSScore :
	public GameStateBase
{
public:
	GSScore();
	~GSScore();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::vector< std::shared_ptr<Sprite2D>> m_listObjects;
	SoLoud::Soloud* soloud = new SoLoud::Soloud;
	std::shared_ptr<Text> m_score;

};
