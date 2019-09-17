#pragma once
#include "AnimationSprite.h"

class timeline : public AnimationSprite
{
private:
	int m_numFrames;
	int m_currentFrame;
	float m_delayTime;
	float m_currentDisplayTime;

public:
	timeline(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float delayTime);
	~timeline();

	void Update(float deltaTime) override;
	void PlayAnimation();
};