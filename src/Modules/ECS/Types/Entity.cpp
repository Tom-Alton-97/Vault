#include "Entity.h"

const EntityActiveStatus Entity::getEntityStatus() const noexcept
{
	return this->entityStatus;
}

void Entity::setEntityStatusActive() noexcept
{
	this->entityStatus.store(EntityActiveStatus::EntityActive);
}

void Entity::setEntityStatusDisabled() noexcept
{
	this->entityStatus.store(EntityActiveStatus::EntityDisabled);
}