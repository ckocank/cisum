#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "soloud.h"
#include "soloud_wav.h"
#include <string>

class AnimationSprite;
class Sprite3D;
class Text;
class Sprite2D;
extern float scale;


class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	
	void SetNewPostionForBullet();

	static BOOLEAN Check();

private:

	std::shared_ptr<Sprite2D> m_BackGround, m_Timeleft1, m_Timeleft2, m_TimeleftBG, m_Select, m_Right;
	std::shared_ptr<Text>  m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::vector< std::shared_ptr<AnimationSprite>> m_listObjects;
	
	std::vector<std::string> m_songList, m_song;
	
	SoLoud::Soloud* soloud = new SoLoud::Soloud;
	SoLoud::Wav gamesong;
	
	float m_time;
	int x_select, y_select, x_correct, y_correct;
	int x_scale;

};

