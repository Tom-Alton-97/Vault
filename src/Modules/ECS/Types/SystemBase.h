#pragma once

#include <vector>
#include <cstdint>
#include <unordered_set>

#include "Entity.h"

namespace ECS_System
{
	class SystemBase
	{
	public:
		virtual ~SystemBase() = default;
		virtual void update(const float argDeltaTime) = 0; 
		// we can potentially have a component for movement updates that stores the values to be updated at a given delta
		// we can then consume the components data per the update override

	protected:
	private:
	};
}