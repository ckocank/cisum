#include "GSSettings.h"
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

GSSettings::GSSettings()
{
}

GSSettings::~GSSettings()
{
}

void GSSettings::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg-setting");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//back bt
	texture = ResourceManagers::GetInstance()->GetTexture("back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(60 * scale, 60 * scale);
	button->SetSize(118 * scale, 90 * scale);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	//credit bt
	texture = ResourceManagers::GetInstance()->GetTexture("bt_cre");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 870 * scale);
	button->SetSize(329 * scale, 131 * scale);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Credit);
		});
	m_listButton.push_back(button);

	
	
}

void GSSettings::Exit()
{
}

void GSSettings::Pause()
{
}

void GSSettings::Resume()
{
}

void GSSettings::HandleEvents()
{
}

void GSSettings::HandleKeyEvents(int key, bool bIsPressed)
{
}
void GSSettings::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSSettings::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}
void GSSettings::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}
