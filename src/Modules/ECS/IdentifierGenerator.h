#pragma once

#include <memory>
#include <set>

namespace ECS_System
{
	using IdentifierUnderlyingType = std::uint_least64_t;

	enum class IdentifierType : std::uint_fast8_t
	{
		EntityType = 1 << 0,
		ComponentType = 1 << 1,
		SystemType = 1 << 2
	};

	class IdentifierGenerator
	{
	public:

		static inline [[nodiscard]] std::unique_ptr<IdentifierGenerator>& getInstance()
		{
			static std::unique_ptr<IdentifierGenerator> instance{ new IdentifierGenerator() };

			return instance;
		}

		IdentifierUnderlyingType [[nodiscard]] generateIdentifier(IdentifierType const argIdentifierType) noexcept;
		const bool reclaimIdentifier(IdentifierType const argIdentifierType, IdentifierUnderlyingType const argIdentifier) noexcept;

	protected:
	private:

		friend struct std::default_delete<IdentifierGenerator>;

		std::set<IdentifierUnderlyingType> [[nodiscard]] & getInferredContainer(IdentifierType const argIdentifierType);
		std::set<IdentifierUnderlyingType> [[nodiscard]] & getInferredReclaimedContainer(IdentifierType const argIdentifierType);
		IdentifierUnderlyingType [[nodiscard]] & getNextInferredTypeIdentifier(IdentifierType const argIdentifierType);

		IdentifierUnderlyingType const [[nodiscard]] internalGenerateIdentifier(IdentifierType const argIdentifierType) noexcept;
		bool [[nodiscard]] const hasValidTypeIdentifierAvailable(IdentifierType const argIdentifierType, IdentifierUnderlyingType const argNextIdentifier) noexcept;

		IdentifierUnderlyingType nextEntityTypeIdentifier{ 0 };
		IdentifierUnderlyingType nextComponentTypeIdentifier{ 0 };
		IdentifierUnderlyingType nextSystemTypeIdentifier{ 0 };

		std::set<IdentifierUnderlyingType> entityTypeIdentifiers{};
		std::set<IdentifierUnderlyingType> componentTypeIdentifiers{};
		std::set<IdentifierUnderlyingType> systemTypeIdentifiers{};

		std::set<IdentifierUnderlyingType> reclaimedEntityTypeIdentifiers{};
		std::set<IdentifierUnderlyingType> reclaimedComponentTypeIdentifiers{};
		std::set<IdentifierUnderlyingType> reclaimedSystemTypeIdentifiers{};
	};
}