#pragma once

#include <cstdint>

namespace ECS_System
{
	using EntityID = std::uint_fast32_t;

	class IEntity
	{
	public:
		explicit IEntity(const EntityID argGeneratedEntityIdentifier) noexcept : entityIdentifier(argGeneratedEntityIdentifier) {}
		virtual ~IEntity() = default;


		const [[nodiscard]] EntityID getEntityID() const noexcept;

	protected:
		IEntity(const IEntity& argOther) = delete;
		IEntity(IEntity&& argOther) = delete;
		IEntity& operator=(const IEntity& argOther) = delete;
		IEntity& operator=(const IEntity&& argOther) = delete;

	private:
		const EntityID entityIdentifier{};
	};
}