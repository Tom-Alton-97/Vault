#include "IEntity.h"

namespace ECS_System
{
	const EntityID IEntity::getEntityID() const noexcept
	{
		return this->entityIdentifier;
	}
}