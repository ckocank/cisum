#pragma once
#include "AnimationSprite.h"
class Timeleft1 :
	public AnimationSprite
{
public:
	Timeleft1(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr <Texture> texture, int numFrames, float delayTime);
	~Timeleft1();
	void Update(float deltatime);


private:
	int m_numFrames;
	int m_currentFrame;
	float m_delayTime;
	float m_currentDisplayTime;

};

