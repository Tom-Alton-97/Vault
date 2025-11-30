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

	class ManagerBase
	{
	public:

		~ManagerBase() = default;

		IdentifierUnderlyingType [[nodiscard]] generateIdentifier();
		const bool reclaimIdentifier(IdentifierUnderlyingType const argIdentifier) noexcept;
		IdentifierUnderlyingType [[nodiscard]] getReclaimableIdentifier() noexcept;

		void Reset() noexcept;
 
	protected:
		ManagerBase();
	private:

		friend struct std::default_delete<ManagerBase>;
		friend class Singleton<ManagerBase>;

		IdentifierUnderlyingType const [[nodiscard]] internalGenerateIdentifier();

		IdentifierUnderlyingType nextIdentifier{ 0 };
		std::vector<IdentifierUnderlyingType> dense{};
		std::vector<IdentifierUnderlyingType> sparse{};
		std::vector<IdentifierUnderlyingType> reclaimedIdentifiers{};
	};
}