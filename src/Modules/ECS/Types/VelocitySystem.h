#pragma once

#include "SystemBase.h"
#include "ComponentArray.h"
#include "VelocityComponent.h"
#include "ComponentManager.h"

namespace ECS_System
{
	class VelocitySystem : public SystemBase
	{
	public:
		VelocitySystem() = default;

		void update(const float argDeltaTime)
		{
			const auto& entities = ComponentManager::getInstance().getEntitiesWithComponent<VelocityComponent>();

			for (auto& entity : entities)
			{
				auto& velocity = ComponentManager::getInstance().getComponent<VelocityComponent>(entity);

				velocity.x += 2 * argDeltaTime;
				velocity.y += 2 * argDeltaTime;
				velocity.z += 2 * argDeltaTime;
			}
		}
	protected:
	private:
	};
}