#include "wave.h"

wave::wave(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float delayTime)
	: AnimationSprite(model, shader, texture), m_numFrames(numFrames), m_delayTime(delayTime)
{

}

wave::~wave()
{}

void wave::PlayAnimation()
{
	m_currentFrame = 0;
	m_currentDisplayTime = 0.0f;
}

void wave::Update(float deltatTime)
{
	m_currentDisplayTime += deltatTime;
	if (m_currentDisplayTime >= m_delayTime)
	{
		m_currentFrame++;
		if (m_currentFrame > m_numFrames)
		{
			m_currentFrame = 0;
		}
	}
}