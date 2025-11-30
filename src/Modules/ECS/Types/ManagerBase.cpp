#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <numeric>

#include "ManagerBase.h"

namespace ECS_System
{
	void ManagerBase::Reset() noexcept
	{
		nextIdentifier = 0;
		dense.clear();
		sparse.clear();
		reclaimedIdentifiers.clear();
	}

	IdentifierUnderlyingType ManagerBase::generateIdentifier()
	{
		//IdentifierUnderlyingType returnValue{};

		//returnValue = internalGenerateIdentifier();

		//identifiers.push_back(returnValue);
		//identifierToIndex.insert({ returnValue, identifiers.size() - 1});

		return internalGenerateIdentifier();
	}

	const bool ManagerBase::reclaimIdentifier(const IdentifierUnderlyingType argIdentifier) noexcept
	{
		if (argIdentifier >= sparse.size() || sparse[argIdentifier] == std::numeric_limits<IdentifierUnderlyingType>::max())
		{
			return false;
		}

		auto index = sparse[argIdentifier];
		auto lastIndex = dense.back();
		dense[index] = lastIndex;
		sparse[lastIndex] = index;

		dense.pop_back();
		sparse[argIdentifier] = std::numeric_limits<IdentifierUnderlyingType>::max();
		reclaimedIdentifiers.push_back(argIdentifier);

		return true;

		///////////////////

		//auto reclaimedIdentifierIterator{ identifierToIndex.find(argIdentifier) };

		//if (reclaimedIdentifierIterator == identifierToIndex.end())
		//{
		//	// TODO log
		//	returnValue = false;
		//}
		//else
		//{
		//	size_t reclaimedIdentifierIndex = reclaimedIdentifierIterator->second;
		//	size_t lastReclaimedIdentifierIndex = identifiers.size() - 1;

		//	std::swap(identifiers[reclaimedIdentifierIndex], identifiers[lastReclaimedIdentifierIndex]);
		//	identifierToIndex[identifiers[reclaimedIdentifierIndex]] = reclaimedIdentifierIndex;


		//	identifiers.pop_back();
		//	identifierToIndex.erase(argIdentifier);
		//	reclaimedIdentifiers.push_back(argIdentifier);
		//}
		//
		//return returnValue;
	}

	IdentifierUnderlyingType [[nodiscard]] ManagerBase::getReclaimableIdentifier() noexcept
	{
		IdentifierUnderlyingType returnValue{ 0 };

		returnValue = reclaimedIdentifiers.back();
		reclaimedIdentifiers.pop_back();

		return returnValue;
	}

	IdentifierUnderlyingType const ManagerBase::internalGenerateIdentifier() // TODO this will break if have max entities and no reclaimables
	{
		IdentifierUnderlyingType returnValue{};

		if (nextIdentifier < std::numeric_limits<IdentifierUnderlyingType>::max())
		{
			returnValue = ++nextIdentifier;
		} 
		else if(!reclaimedIdentifiers.empty())
		{
			returnValue = getReclaimableIdentifier();
		}
		else
		{
			// TODO log
			throw std::out_of_range("Attempted to generate an invalid identifier.");
		}

		if (returnValue >= sparse.size())
		{
			sparse.resize(returnValue + 1, std::numeric_limits<IdentifierUnderlyingType>::max());
		}

		sparse[returnValue] = dense.size();
		dense.push_back(returnValue);

		return returnValue;
	}
}