#include "IEntity.h"

const EntityID IEntity::getEntityID() const noexcept
{
	return this->entityIdentifier;
}
