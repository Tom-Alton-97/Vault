#include "IdentifierGenerator.h"

#include <stdexcept>
#include <iostream>
#include <limits>

namespace ECS_System
{
	IdentifierUnderlyingType ECS_System::IdentifierGenerator::generateIdentifier(const IdentifierType argIdentifierType) noexcept
	{
		IdentifierUnderlyingType localIdentifier{ internalGenerateIdentifier(argIdentifierType) };

		getInferredContainer(argIdentifierType).insert(localIdentifier);

		return localIdentifier;
	}

	const bool ECS_System::IdentifierGenerator::reclaimIdentifier(const IdentifierType argIdentifierType, const IdentifierUnderlyingType argIdentifier) noexcept
	{
		bool returnVal{ false };

		auto& inferredContainer{ getInferredContainer(argIdentifierType) };
		auto localReclaimedIdentifierIterator{ inferredContainer.find(argIdentifier) };

		if (inferredContainer.end() != localReclaimedIdentifierIterator)
		{
			getInferredReclaimedContainer(argIdentifierType).insert(*localReclaimedIdentifierIterator);
			inferredContainer.erase(localReclaimedIdentifierIterator);

			returnVal = true;
		} 
		else
		{
			// TODO log here
			std::cerr << "Tried to reclaim an invalid identifier." << std::endl << std::flush;
		}

		return returnVal;
	}

	IdentifierUnderlyingType const IdentifierGenerator::internalGenerateIdentifier(IdentifierType const argIdentifierType) noexcept
	{
		IdentifierUnderlyingType localNextIdentifier = getNextInferredTypeIdentifier(argIdentifierType);

		if (true == hasValidTypeIdentifierAvailable(argIdentifierType, localNextIdentifier))
		{
			// TODO log message here
			std::cerr << "No valid type identifer available." << std::endl << std::flush;
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