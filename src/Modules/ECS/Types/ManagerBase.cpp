#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "ManagerBase.h"

namespace ECS_System
{
	void ManagerBase::Reset() noexcept
	{
		nextIdentifier = 0;
		identifiers.clear();
		identifierToIndex.clear();
		reclaimedIdentifiers.clear();
	}

	IdentifierUnderlyingType ManagerBase::generateIdentifier()
	{
		IdentifierUnderlyingType returnValue{};

		returnValue = internalGenerateIdentifier();

		identifiers.push_back(returnValue);
		identifierToIndex.insert(returnValue, identifiers.size() - 1);

		return returnValue;
	}

	const bool ManagerBase::reclaimIdentifier(const IdentifierUnderlyingType argIdentifier) noexcept
	{
		bool returnVal{ false };

		auto reclaimedIdentifierIterator{ identifierToIndex.find(argIdentifier) };

		if (reclaimedIdentifierIterator == identifierToIndex.end())
		{
			// TODO log
		}

		size_t reclaimedIdentifierIndex = reclaimedIdentifierIterator->second;
		size_t lastReclaimedIdentifierIndex = identifierToIndex.size() - 1;

		std::swap(identifiers[reclaimedIdentifierIndex], identifiers[lastReclaimedIdentifierIndex]); //check what is faster [] or .at
		identifierToIndex[identifiers[reclaimedIdentifierIndex]] = reclaimedIdentifierIndex;


		identifiers.pop_back();
		identifierToIndex.erase(argIdentifier);
		reclaimedIdentifiers.push_back(argIdentifier);
		
		return returnVal;
	}

	IdentifierUnderlyingType const ManagerBase::internalGenerateIdentifier()
	{
		IdentifierUnderlyingType localNextIdentifier = ++nextIdentifier;

		if (false == hasValidTypeIdentifierAvailable())
		{
			if (!reclaimedIdentifiers.empty())
			{
				localNextIdentifier = getReclaimableIdentifier();
			}

			throw std::out_of_range("Attempted to generate an invalid identifier.");
		}

		return localNextIdentifier;
	}

	IdentifierUnderlyingType [[nodiscard]] ManagerBase::getReclaimableIdentifier() noexcept
	{
		IdentifierUnderlyingType returnValue{ 0 };

		returnValue = reclaimedIdentifiers.back();
		reclaimedIdentifiers.pop_back();

		return returnValue;
	}

	bool [[nodiscard]] const ManagerBase::hasValidTypeIdentifierAvailable() noexcept
	{
		bool returnValue{ false };

		static IdentifierUnderlyingType localMaxUsableValue = -1;

		if (nextIdentifier != localMaxUsableValue)
		{
			returnValue = true;
		}

		return returnValue;
	}
}