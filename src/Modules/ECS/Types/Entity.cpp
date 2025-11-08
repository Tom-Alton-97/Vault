#include "Entity.h"

const EntityActiveStatus Entity::getEntityStatus() const noexcept
{
	return this->entityStatus.load();
}

void Entity::setEntityStatusEnabled() noexcept
{
	this->entityStatus.store(EntityActiveStatus::EntityEnabled);
}

void Entity::setEntityStatusDisabled() noexcept
{
	this->entityStatus.store(EntityActiveStatus::EntityDisabled);
}