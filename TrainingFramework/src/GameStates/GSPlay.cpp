#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "AnimationSprite.h"
#include "Sprite3D.h"
#include "Text.h"
#include "wave.h"

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern float scale;

GSPlay::GSPlay()
{
	m_time = 0;
	x_scale1 = 437 * scale;
	x_scale2 = 437 * scale;
	srand(time(0));
}


GSPlay::~GSPlay()
{
	//delete soloud;
	//soloud = nullptr;
}


void GSPlay::Init()
{
	

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg-game-02");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//timeleft bg
	texture = ResourceManagers::GetInstance()->GetTexture("timeleft_bg");
	m_TimeleftBG = std::make_shared<Sprite2D>(model, shader, texture);
	m_TimeleftBG->Set2DPosition(screenWidth / 2, 50);
	m_TimeleftBG->SetSize(484 * scale, 58 * scale);

	//timeleft 2
	texture = ResourceManagers::GetInstance()->GetTexture("timeleft2");
	m_Timeleft2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_Timeleft2->Set2DPosition(screenWidth / 2, 46);
	m_Timeleft2->SetSize(x_scale2, 25 * scale);
	m_timeline.push_back(m_Timeleft2);

	//timeleft 1
	texture = ResourceManagers::GetInstance()->GetTexture("timeleft1");
	m_Timeleft1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_Timeleft1->Set2DPosition(screenWidth / 2, 46);
	m_Timeleft1->SetSize(x_scale1, 25 * scale);
	m_timeline.push_back(m_Timeleft1);

	//gameover
	texture = ResourceManagers::GetInstance()->GetTexture("gameover");
	gameover = std::make_shared<Sprite2D>(model, shader, texture);
	gameover->Set2DPosition(screenWidth / 2, screenHeight / 2);
	gameover->SetSize(0, 0);


	//answer button
	texture = ResourceManagers::GetInstance()->GetTexture("bt_anw");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 470 * scale);
	button->SetSize(401 * scale, 125 * scale);
	button->SetOnClick([]() {

		});
	m_listButton.push_back(button);

	//answer button
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 670 * scale);
	button->SetSize(401 * scale, 125 * scale);
	button->SetOnClick([]() {

		});
	m_listButton.push_back(button);


	//answer button
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 870 * scale);
	button->SetSize(401 * scale, 125 * scale);
	button->SetOnClick([]() {

		});
	m_listButton.push_back(button);

	//selected answer
	texture = ResourceManagers::GetInstance()->GetTexture("bt_anw2");
	m_Select = std::make_shared<Sprite2D>(model, shader, texture);
	m_Select->Set2DPosition(x_select, y_select);
	m_Select->SetSize(401 * scale, 125 * scale);

	//corect answer
	texture = ResourceManagers::GetInstance()->GetTexture("bt_crt");
	m_Right = std::make_shared<Sprite2D>(model, shader, texture);
	m_Right->Set2DPosition(x_correct, y_correct);
	m_Right->SetSize(401 * scale, 125 * scale);

	//back bt
	texture = ResourceManagers::GetInstance()->GetTexture("back");
	backButton= std::make_shared<GameButton>(model, shader, texture);
	backButton->Set2DPosition(screenWidth / 2, (screenHeight / 2) + 120);
	backButton->SetSize(0,0);
	backButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});

	auto waveModel = ResourceManagers::GetInstance()->GetModel("sprite2d");
	auto waveTexture = ResourceManagers::GetInstance()->GetTexture("longwave");
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	std::shared_ptr<AnimationSprite> waveSound = std::make_shared<AnimationSprite>(waveModel, shader, waveTexture, 4, 0.1);
	waveSound->Set2DPosition(275 * scale, 320 * scale);
	waveSound->SetSize(507 * scale, 500 * scale);
	m_listObjects.push_back(waveSound);



	


	//load duong dan list nhac

	std::ifstream file_("../Data/music/listsong.txt");
	if (file_.is_open())
	{
		while (getline(file_, line_))
		{
			m_songList.push_back(line_);
			std::cout << line_ << '\n';
		}
		file_.close();
	}

	//menu song
	soloud->init();

	gamesong.load(m_songList[0].c_str());
	soloud->play(gamesong);

	sname1 = m_songList[0].c_str();
	sname1.replace(0, 14, "");
	for (int i = 0; i < 4; i++)
		sname1.pop_back();

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("calibri");
	std::shared_ptr<Text> m_name = std::make_shared< Text>(shader, font, sname1, TEXT_COLOR::WHILE, 1.0);
	m_name->Set2DPosition(Vector2(screenWidth / 2- 70, 870 * scale));
	song.push_back(m_name);

	sname2 = m_songList[1].c_str();
	sname2.replace(0, 14, "");
	for (int i = 0; i < 4; i++)
		sname2.pop_back();

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("calibri");
	m_name = std::make_shared< Text>(shader, font, sname2, TEXT_COLOR::WHILE, 1.0);
	m_name->Set2DPosition(Vector2(screenWidth / 2 - 70, 670 * scale));
	song.push_back(m_name);

	sname3 = m_songList[2].c_str();
	sname3.replace(0, 14, "");
	for (int i = 0; i < 4; i++)
		sname3.pop_back();

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("calibri");
	m_name = std::make_shared< Text>(shader, font, sname3, TEXT_COLOR::WHILE, 1.0);
	m_name->Set2DPosition(Vector2(screenWidth / 2 - 70, 470 * scale));
	song.push_back(m_name);
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
	backButton->HandleTouchEvents(x, y, bIsPressed);

}

void GSPlay::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto obj : m_listObjects)
	{
		obj->Update(deltaTime);
	}
	for (auto obj : song)
	{
		obj->Update(deltaTime);
	}
	
	m_time += deltaTime;
	if (m_time <= 25.0f)
	{
		
		if (m_time < 15)
		{
			x_scale1 -= deltaTime;
			m_Timeleft1->SetSize(x_scale1, 25 * scale);
		}
		else
		{
			x_scale2 -= deltaTime;
			m_Timeleft2->SetSize(x_scale2, 25 * scale);

		}
}
	else
	{
		backButton->SetSize(118 * scale, 90 * scale);
		gameover->SetSize(331, 396);
		soloud->deinit();
		m_time = 0;
	}

}


void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_TimeleftBG->Draw();
	
	
	for (auto obj : m_timeline)
	{
		obj->Draw();
	}
	for (auto obj : m_listObjects)
	{
		obj->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto obj : song)
	{
		obj->Draw();
	}
	gameover->Draw();
	backButton->Draw();

}


BOOLEAN GSPlay::Check()
{
	return BOOLEAN();
}
