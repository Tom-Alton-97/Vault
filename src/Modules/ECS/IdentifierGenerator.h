#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

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

		void Reset() noexcept;

	protected:
	private:

		friend struct std::default_delete<IdentifierGenerator>;

		std::vector<IdentifierUnderlyingType> [[nodiscard]] & getInferredContainer(IdentifierType const argIdentifierType);
		std::vector<IdentifierUnderlyingType> [[nodiscard]] & getInferredReclaimedContainer(IdentifierType const argIdentifierType);
		IdentifierUnderlyingType [[nodiscard]] & getNextInferredTypeIdentifier(IdentifierType const argIdentifierType);

		IdentifierUnderlyingType const [[nodiscard]] internalGenerateIdentifier(IdentifierType const argIdentifierType) noexcept;
		IdentifierUnderlyingType [[nodiscard]] getReclaimableIdentifier(IdentifierType const argIdentifierType) noexcept;
		bool [[nodiscard]] const hasValidTypeIdentifierAvailable(IdentifierType const argIdentifierType, IdentifierUnderlyingType const argNextIdentifier) noexcept;

		IdentifierUnderlyingType nextEntityTypeIdentifier{ 0 };
		IdentifierUnderlyingType nextComponentTypeIdentifier{ 0 };
		IdentifierUnderlyingType nextSystemTypeIdentifier{ 0 };

		std::vector<IdentifierUnderlyingType> entityTypeIdentifiers{};
		std::vector<IdentifierUnderlyingType> componentTypeIdentifiers{};
		std::vector<IdentifierUnderlyingType> systemTypeIdentifiers{};

		std::unordered_map<IdentifierUnderlyingType, size_t> entityIdentifierToIndex;
		std::unordered_map<IdentifierUnderlyingType, size_t> componentIdentifierToIndex;
		std::unordered_map<IdentifierUnderlyingType, size_t> systemIdentifierToIndex;

		std::vector<IdentifierUnderlyingType> reclaimedEntityTypeIdentifiers{};
		std::vector<IdentifierUnderlyingType> reclaimedComponentTypeIdentifiers{};
		std::vector<IdentifierUnderlyingType> reclaimedSystemTypeIdentifiers{};
	};
}