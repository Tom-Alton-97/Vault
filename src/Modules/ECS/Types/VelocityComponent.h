#pragma once

#include "ComponentBase.h"

namespace ECS_System
{
	class VelocityComponent : public ComponentBase
	{
	public:
		VelocityComponent(float argX = 0.0f , float argY = 0.0f, float argZ = 0.0f) : x(argX), y(argY), z(argZ) {}

		// TODO Rule of 5

		float x{ 0.0f };
		float y{ 0.0f };
		float z{ 0.0f };
	protected:
	private:
	};
}