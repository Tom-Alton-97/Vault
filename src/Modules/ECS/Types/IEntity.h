#pragma once

#include <cstdint>

using EntityID = std::uint_fast32_t;

class IEntity
{
public:
	explicit IEntity(const EntityID argGeneratedEntityIdentifier) noexcept : entityIdentifier(argGeneratedEntityIdentifier) {}
	virtual ~IEntity() = default;

	[[nodiscard]]
	const EntityID getEntityID() const noexcept;

protected:
	IEntity(const IEntity& argOther) = delete;
	IEntity(IEntity&& argOther) = delete;
	IEntity& operator=(const IEntity& argOther) = delete;
	IEntity& operator=(const IEntity&& argOther) = delete;

private:
	const EntityID entityIdentifier{};
};