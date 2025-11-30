#pragma once

#include "Entity.h"

namespace ECS_System
{
	class ComponentArrayBase
	{
	public:
		virtual ~ComponentArrayBase() = default;
		virtual const std::vector<EntityID>& getEntities() const noexcept = 0;
	protected:
	private:
	};
}