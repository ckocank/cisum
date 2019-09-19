#include "GSMenu.h"


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern float scale;

SoLoud::Soloud* GSMenu::soloud = new SoLoud::Soloud;
SoLoud::Wav* GSMenu::menusong = new SoLoud::Wav;
static int handle;

GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
	//delete soloud;
}



void GSMenu::Init()
{
	//menu song
	soloud->init();
	menusong->load("../Data/sfx/straight.mp3");
	menusong->setLooping(1);
	
	handle = soloud->play(*menusong);
	



	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg-menu-01");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//banner
	texture = ResourceManagers::GetInstance()->GetTexture("banner");
	banner = std::make_shared<Sprite2D>(model, shader, texture);
	banner->Set2DPosition(screenWidth / 2, screenHeight - 30);
	banner->SetSize(400, 100);


	//MUTE button
	texture = ResourceManagers::GetInstance()->GetTexture("speaker1");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth -30, 30);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		float v = soloud->getVolume(handle);
		soloud->setVolume(handle, 0.0f);
		});
	m_listButton.push_back(button);

	//UNMUTE button
	texture = ResourceManagers::GetInstance()->GetTexture("speaker");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(30, 30);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		float v = soloud->getVolume(handle);
		soloud->setVolume(handle, 1.0f);
		});
	m_listButton.push_back(button);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("bt_ply");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 , 450 * scale);
	button->SetSize(372 * scale, 153 * scale);
	button->SetOnClick([]() {
		float v = soloud->getVolume(handle);
		soloud->setVolume(handle, 0.0f);
		//soloud->stopAudioSource(*menusong);
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//credit button
	texture = ResourceManagers::GetInstance()->GetTexture("bt_st");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 850 * scale);
	button->SetSize(372 *scale, 153 * scale);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Credit);
		});
	m_listButton.push_back(button);

	//scores button
	texture = ResourceManagers::GetInstance()->GetTexture("bt_scr");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 650 * scale);
	button->SetSize(368 * scale, 151 * scale);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Score);
		});
	m_listButton.push_back(button);

	//delete banner button
	texture = ResourceManagers::GetInstance()->GetTexture("delete");
	delbutton = std::make_shared<GameButton>(model, shader, texture);
	delbutton->Set2DPosition(screenWidth -22, screenHeight - 66);
	delbutton->SetSize(20, 20);
	delbutton->SetOnClick([]() {
		
		});
	

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName = std::make_shared< Text>(shader, font, "", TEXT_COLOR::GREEN, 1.0);
	m_Text_gameName->Set2DPosition(Vector2(screenWidth / 2 - 80, 120));
	
	

}
void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{
	float v = soloud->getVolume(handle);
	soloud->setVolume(handle, 1.0f);
}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle())
			break;
	}
	delbutton->HandleTouchEvents(x, y, bIsPressed);
	
	if (delbutton->IsHandle())
	{
		delbutton->SetSize(0, 0);
		banner->SetSize(0, 0);
	}
}

void GSMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	banner->Update(deltaTime);
	delbutton->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	banner->Draw();
	delbutton->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
}


