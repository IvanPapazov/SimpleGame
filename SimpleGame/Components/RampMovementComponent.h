#pragma once
#include "stdafx.h"
#include <Components/AIComponent.h>

class RampMovementComponent : public AIComponent
{
public:
	~RampMovementComponent() = default;
	RampMovementComponent(int speed);
	void Update();
};