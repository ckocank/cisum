#include "timeline.h"

timeline::timeline(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float delayTime)
	: AnimationSprite(model, shader, texture), m_delayTime(delayTime)
{

}

timeline::~timeline()
{}

void timeline::PlayAnimation()
{

}

void timeline::Update(float deltatTime)
{
	
}