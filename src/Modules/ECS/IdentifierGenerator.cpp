#include "IdentifierGenerator.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace ECS_System
{
	void IdentifierGenerator::Reset() noexcept
	{
		nextEntityTypeIdentifier = 0;
		nextComponentTypeIdentifier = 0;
		nextSystemTypeIdentifier = 0;
		entityTypeIdentifiers.clear();
		componentTypeIdentifiers.clear();
		systemTypeIdentifiers.clear();
		reclaimedEntityTypeIdentifiers.clear();
		reclaimedComponentTypeIdentifiers.clear();
		reclaimedSystemTypeIdentifiers.clear();
	}

	IdentifierUnderlyingType IdentifierGenerator::generateIdentifier(const IdentifierType argIdentifierType) noexcept
	{
		IdentifierUnderlyingType returnValue{};

		auto& inferredContainer{ getInferredContainer(argIdentifierType) };

		returnValue = internalGenerateIdentifier(argIdentifierType);

		inferredContainer.push_back(returnValue);

		return returnValue;
	}

	const bool IdentifierGenerator::reclaimIdentifier(const IdentifierType argIdentifierType, const IdentifierUnderlyingType argIdentifier) noexcept
	{
		bool returnVal{ false };

		auto& inferredContainer{ getInferredContainer(argIdentifierType) };
		auto localReclaimedIdentifierIterator = std::find(inferredContainer.begin(), inferredContainer.end(), argIdentifier);

		if (inferredContainer.end() != localReclaimedIdentifierIterator)
		{
			getInferredReclaimedContainer(argIdentifierType).push_back(*localReclaimedIdentifierIterator);

			std::iter_swap(localReclaimedIdentifierIterator, inferredContainer.end() - 1);
			inferredContainer.pop_back();

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


		if (false == hasValidTypeIdentifierAvailable(argIdentifierType, localNextIdentifier))
		{
			if (!getInferredReclaimedContainer(argIdentifierType).empty())
			{
				localNextIdentifier = getReclaimableIdentifier(argIdentifierType);
			}
		}

		return localNextIdentifier;
	}

	IdentifierUnderlyingType [[nodiscard]] IdentifierGenerator::getReclaimableIdentifier(IdentifierType const argIdentifierType) noexcept
	{
		IdentifierUnderlyingType returnValue{ 0 };
		std::vector<IdentifierUnderlyingType>& localInferredReclaimedContainer = getInferredReclaimedContainer(argIdentifierType);

		returnValue = localInferredReclaimedContainer.back();
		localInferredReclaimedContainer.pop_back();

		return returnValue;
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

	std::vector<IdentifierUnderlyingType>& IdentifierGenerator::getInferredContainer(const IdentifierType argIdentifierType)
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
	std::vector<IdentifierUnderlyingType> [[nodiscard]] & IdentifierGenerator::getInferredReclaimedContainer(IdentifierType const argIdentifierType)
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
	IdentifierUnderlyingType& IdentifierGenerator::getNextInferredTypeIdentifier(IdentifierType const argIdentifierType)
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