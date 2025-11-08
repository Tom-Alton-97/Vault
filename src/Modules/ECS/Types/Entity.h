#pragma once

#include <atomic>
#include "IEntity.h"

enum class EntityActiveStatus : std::uint_fast8_t
{
	EntityEnabled = 1 << 0,
	EntityDisabled = 1 << 1
};

class Entity : public IEntity
{
public:
	explicit Entity(const EntityID argGeneratedEntityIdentifier) noexcept : IEntity(argGeneratedEntityIdentifier) {}

	[[nodiscard]]
	const EntityActiveStatus getEntityStatus() const noexcept;
	void setEntityStatusEnabled() noexcept;
	void setEntityStatusDisabled() noexcept;

protected:
	Entity(const Entity& argOther) = delete;
	Entity(Entity&& argOther) = delete;
	Entity& operator=(const Entity& argOther) = delete;
	Entity& operator=(const Entity&& argOther) = delete;

private:
	volatile std::atomic<EntityActiveStatus> entityStatus{ EntityActiveStatus::EntityEnabled };
};