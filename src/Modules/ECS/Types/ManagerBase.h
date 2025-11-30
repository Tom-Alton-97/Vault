#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>

#include "Singleton.h"

namespace ECS_System
{
	using IdentifierUnderlyingType = std::uint_least64_t;

	enum class IdentifierType : std::uint_fast8_t
	{
		EntityType = 1 << 0,
		ComponentType = 1 << 1,
		SystemType = 1 << 2
	};

	class ManagerBase : private Singleton<ManagerBase>
	{
		friend struct std::default_delete<ManagerBase>;
		friend class Singleton<ManagerBase>;

		void destructor() noexcept override
		{
			Reset();
		}

		~ManagerBase() = default;

		IdentifierUnderlyingType [[nodiscard]] generateIdentifier();
		const bool reclaimIdentifier(IdentifierUnderlyingType const argIdentifier) noexcept;

		void Reset() noexcept;

	protected:
	private:

		friend struct std::default_delete<ManagerBase>;

		IdentifierUnderlyingType const [[nodiscard]] internalGenerateIdentifier();
		IdentifierUnderlyingType [[nodiscard]] getReclaimableIdentifier() noexcept;
		bool [[nodiscard]] const hasValidTypeIdentifierAvailable() noexcept;

		IdentifierUnderlyingType nextIdentifier{ 0 };
		std::vector<IdentifierUnderlyingType> identifiers{};
		std::unordered_map<IdentifierUnderlyingType, size_t> identifierToIndex;
		std::vector<IdentifierUnderlyingType> reclaimedIdentifiers{};
	};
}