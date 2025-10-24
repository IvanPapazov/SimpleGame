#pragma once
#include "stdafx.h"


class CollisionComponent : public Component
{
private:
	float m_X, m_Y;
	float m_Width, m_Height;

	bool left = true;
	bool right = true;
	bool bottom = true;
	bool hit = false;
public:
	~CollisionComponent() = default;
	CollisionComponent(float x, float y, float w, float h)
		: m_X(x), m_Y(y), m_Width(w), m_Height(h) {};

	void Update(GameObject* object);
	bool CheckCollision(CollisionComponent* a, CollisionComponent* b);

	bool IsLeft() const { return left; }
	bool IsRight() const { return right; }
	bool IsBottom() const { return bottom; }
	bool IsHit() const { return hit; }

	void SetLeft(bool value) { left = value; }
	void SetRight(bool value) { right = value; }
	void SetBottom(bool value) { bottom = value; }
	void SetHit(bool value) { hit = value; }
};

