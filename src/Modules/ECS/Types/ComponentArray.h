#pragma once

#include <vector>

#include "Entity.h"

namespace ECS_System
{
	template<typename T>
	class ComponentArray
	{
		std::vector<T> components;
		std::vector<EntityID, size_t> entityToIndex;
		std::vector<EntityID> indexToEntity;
	};
}