#pragma once
#include "AnimationSprite.h"

class wave : public AnimationSprite
{
private:
	int m_numFrames;
	int m_currentFrame;
	float m_delayTime;
	float m_currentDisplayTime;

public:
	wave(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float delayTime);
	~wave();
	//void Pause();
	//void Resume();

	void Update(float deltaTime) override;
	void PlayAnimation();
};