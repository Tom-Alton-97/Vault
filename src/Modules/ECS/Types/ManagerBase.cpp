#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <numeric>

#include "EntityManager.h"

namespace
{
	static constexpr std::size_t PREALLOCATE_EXPECTED_MAX_IDENTIFIERS{ 10'000'000 };
}

namespace ECS_System
{
	ManagerBase::ManagerBase()
	{
		dense.reserve(PREALLOCATE_EXPECTED_MAX_IDENTIFIERS);
		sparse.reserve(PREALLOCATE_EXPECTED_MAX_IDENTIFIERS);
		reclaimedIdentifiers.reserve(PREALLOCATE_EXPECTED_MAX_IDENTIFIERS / 2);
	}

	void ManagerBase::Reset() noexcept
	{
		nextIdentifier = 0;
		dense.clear();
		sparse.clear();
		reclaimedIdentifiers.clear();
	}

	IdentifierUnderlyingType ManagerBase::generateIdentifier()
	{
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