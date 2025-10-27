#pragma once
#include "stdafx.h"


class CollisionComponent : public Component
{
private:
	float m_X, m_Y;
	float m_Width, m_Height;

	bool m_Left = true;
	bool m_Right = true;
	bool m_Bottom = true;
	bool m_Top = true;
	bool m_Hit = false;
public:
	~CollisionComponent() = default;
	CollisionComponent(float x, float y, float w, float h)
		: m_X(x), m_Y(y), m_Width(w), m_Height(h) {};

	void Update(GameObject* object);
	bool CheckCollision(CollisionComponent* a, CollisionComponent* b);

	bool IsLeft() const { return m_Left; }
	bool IsRight() const { return m_Right; }
	bool IsBottom() const { return m_Bottom; }
	bool IsHit() const { return m_Hit; }
	bool IsTop() const { return m_Top; }

	void SetLeft(bool value) { m_Left = value; }
	void SetRight(bool value) { m_Right = value; }
	void SetBottom(bool value) { m_Bottom = value; }
	void SetHit(bool value) { m_Hit = value; }
	void SetTop(bool value) { m_Top = value; }
};

