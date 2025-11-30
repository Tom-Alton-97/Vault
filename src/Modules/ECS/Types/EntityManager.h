#pragma once

#include "ManagerBase.h"
#include "Singleton.h"
#include "Entity.h"

namespace ECS_System
{
	class EntityManager : public ManagerBase, public Singleton<EntityManager>
	{
	public:
		EntityID createEntity() { return generateIdentifier(); }
		void destroyEntity(EntityID argEntityToDestroy) { reclaimIdentifier(argEntityToDestroy); }

		void destructor() noexcept override
		{
			Reset();
		}
	protected:
	private:
	};
}