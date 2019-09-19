#include "GSScore.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "AnimationSprite.h"
#include "Sprite3D.h"
#include "Text.h"


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern float scale;

GSScore::GSScore()
{
}

GSScore::~GSScore()
{
}

void GSScore::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg-score");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth , screenHeight );

	texture = ResourceManagers::GetInstance()->GetTexture("back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(70 * scale, 70 * scale);
	button->SetSize(118 * scale, 90 * scale);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);
	
	//load score
	std::string score_;
	std::ifstream file_("khongphaiscore.txt");
	if (file_.is_open())
	{
		while (getline(file_, score_))
		{
			std::cout << score_ << '\n';
		}
		file_.close();
	}
	
	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Cooper Std Black Italic");
	m_score = std::make_shared< Text>(shader, font, score_, TEXT_COLOR::WHILE, 3.0);
	m_score->Set2DPosition(Vector2(screenWidth / 2 -10, screenHeight /2));
}

void GSScore::Exit()
{
}

void GSScore::Pause()
{
}

void GSScore::Resume()
{
}

void GSScore::HandleEvents()
{
}

void GSScore::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSScore::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSScore::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSScore::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_score->Draw();
}
