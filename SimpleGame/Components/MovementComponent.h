#pragma once
#include "stdafx.h"
#include <Components/CollisionComponent.h>
class MovementComponent : public System
{
private:
	float m_GravityScale = 9.8f;
	float m_Speed = 3;
	float m_Jump = 7;
	float m_DeltaTimeLast = 0;
	float m_DeltaTime;
public:
	~MovementComponent()=default;
	MovementComponent(){};
	void Update(GameObject* object);
};
