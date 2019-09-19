#include "Timeleft1.h"

Timeleft1::Timeleft1(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float delayTime)
	: AnimationSprite(model, shader, texture), m_numFrames(numFrames), m_delayTime(delayTime)
{
	
}

Timeleft1::~Timeleft1()
{
}

void Timeleft1::Update(float deltatime)
{
	m_currentDisplayTime += deltatime;
	if (m_currentDisplayTime >= m_delayTime)
	{
		m_currentFrame++;
		if (m_currentFrame > m_numFrames)
		{
			m_currentFrame = 0;
		}
	}
}