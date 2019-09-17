#pragma once
#include "baseobject.h"

class AnimationSprite : public BaseObject
{
private:
	std::string		m_Text;
	void			CaculateWorldMatrix();
protected:
	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;
	int m_numFrames;
	int m_currentFrame;
	float m_delayTime;
	float m_currentDisplayTime;

public:
	AnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames = 1, float delayTime = 0.0f);
	AnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color);
	~AnimationSprite();

	void		Init() override;
	void		Draw() final;
	void		Update(GLfloat deltatime) override;

	void		SetText(std::string text);
	std::string	GetText();

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);

	Vector2		Get2DPosition();
	void		SetSize(GLint width, GLint height);

};

