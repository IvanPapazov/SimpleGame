#pragma once
#include "stdafx.h"
#include <Components/AIComponent.h>

class RampMovementComponent : public AIComponent
{
public:
	~RampMovementComponent() = default;
	RampMovementComponent(float speed);
	void Update();
};