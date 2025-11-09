#include "IdentifierGenerator.h"

#include <stdexcept>

namespace ECS_System
{
	IdentifierUnderlyingType ECS_System::IdentifierGenerator::generateIdentifier(const IdentifierType argIdentifierType) noexcept
	{
		IdentifierUnderlyingType localIdentifier{ internalGenerateIdentifier(argIdentifierType) };

		getInferredContainer(argIdentifierType).insert(localIdentifier);

		return localIdentifier;
	}

	inline void ECS_System::IdentifierGenerator::reclaimIdentifier(const IdentifierType argIdentifierType, const IdentifierUnderlyingType argIdentifier) noexcept
	{
		auto localReclaimedIdentifierIterator = getInferredReclaimedContainer(argIdentifierType).find(argIdentifier);

		getInferredReclaimedContainer(argIdentifierType).erase(localReclaimedIdentifierIterator);
	}

	IdentifierUnderlyingType const IdentifierGenerator::internalGenerateIdentifier(IdentifierType const argIdentifierType)
	{
		IdentifierUnderlyingType localNextIdentifier = getNextInferredTypeIdentifier(argIdentifierType);

		if (hasValidTypeIdentifierAvailable(argIdentifierType, localNextIdentifier))
		{
			throw std::out_of_range("Next Identifier is out of range.");
		}

		return localNextIdentifier;
	}

	bool [[nodiscard]] const IdentifierGenerator::hasValidTypeIdentifierAvailable(IdentifierType const argIdentifierType, IdentifierUnderlyingType const argNextIdentifier) noexcept
	{
		static IdentifierUnderlyingType localMaxUsableValue = -1;

		if (argNextIdentifier == localMaxUsableValue)
		{
			return false;
		}

		return !getInferredReclaimedContainer(argIdentifierType).empty();
	}

	std::set<IdentifierUnderlyingType>& ECS_System::IdentifierGenerator::getInferredContainer(const IdentifierType argIdentifierType)
	{
		switch (argIdentifierType)
		{
		case IdentifierType::EntityType:
		{
			return entityTypeIdentifiers;
			break;
		}
		case IdentifierType::ComponentType:
		{
			return componentTypeIdentifiers;
			break;
		}
		case IdentifierType::SystemType:
		{
			return systemTypeIdentifiers;
			break;
		}
		}

		throw std::invalid_argument("Identifier type was invalid.");
	}
	std::set<IdentifierUnderlyingType> [[nodiscard]] & IdentifierGenerator::getInferredReclaimedContainer(IdentifierType const argIdentifierType)
	{
		switch (argIdentifierType)
		{
		case IdentifierType::EntityType:
		{
			return reclaimedEntityTypeIdentifiers;
			break;
		}
		case IdentifierType::ComponentType:
		{
			return reclaimedComponentTypeIdentifiers;
			break;
		}
		case IdentifierType::SystemType:
		{
			return reclaimedSystemTypeIdentifiers;
			break;
		}
		}

		throw std::invalid_argument("Identifier type was invalid.");
	}
	IdentifierUnderlyingType&  ECS_System::IdentifierGenerator::getNextInferredTypeIdentifier(IdentifierType const argIdentifierType)
	{
		switch (argIdentifierType)
		{
		case IdentifierType::EntityType:
		{
			return ++nextEntityTypeIdentifier;
			break;
		}
		case IdentifierType::ComponentType:
		{
			return ++nextComponentTypeIdentifier;
			break;
		}
		case IdentifierType::SystemType:
		{
			return ++nextSystemTypeIdentifier;
			break;
		}
		}

		throw std::invalid_argument("Identifier type was invalid.");
	}
}