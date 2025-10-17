#pragma once

class CollisionComponent
{
private:
	float m_X, m_Y;
	float m_Width, m_Height;
public:
	CollisionComponent(float x, float y, float w, float h)
		: m_X(x), m_Y(y), m_Width(w), m_Height(h) {};
};

