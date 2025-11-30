#pragma once

#include <vector>
#include <algorithm>

#include "Entity.h"
#include "ComponentArrayBase.h"

namespace ECS_System
{
	template<typename T>
	class ComponentArray : public ComponentArrayBase
	{
	public:

		ComponentArray() = default;

		T& get(const EntityID argEntityIdenfitier)
		{
			if (argEntityIdenfitier >= entityToIndex.size() || entityToIndex[argEntityIdenfitier] == invalidIndex)
			{
				throw std::out_of_range("Component not found for entity.");
			}

			return dense[entityToIndex[argEntityIdenfitier]];
		}

		void insert(const EntityID argEntityIdentifierToInsert, const T& argComponentToInsert) noexcept
		{
			if (entityToIndex.size() <= argEntityIdentifierToInsert) entityToIndex.resize(argEntityIdentifierToInsert + 1, invalidIndex);

			if (entityToIndex[argEntityIdentifierToInsert] != invalidIndex) {
				dense[entityToIndex[argEntityIdentifierToInsert]] = argComponentToInsert; // overwrite
				return;
			}

			size_t index = dense.size();
			dense.push_back(argComponentToInsert);
			indexToEntity.push_back(argEntityIdentifierToInsert);
			entityToIndex[argEntityIdentifierToInsert] = index;
		}

		void remove(const EntityID argEntityIdentifierToRemove) noexcept
		{
			if (argEntityIdentifierToRemove >= entityToIndex.size() || entityToIndex[argEntityIdentifierToRemove] == invalidIndex)
			{
				return;
			}

			const size_t index = entityToIndex[argEntityIdentifierToRemove];
			const size_t lastIndex = dense.size() - 1;

			std::swap(dense[index], dense[lastIndex]);
			std::swap(indexToEntity[index], indexToEntity[lastIndex]);

			entityToIndex[indexToEntity[index]] = index;
			entityToIndex[argEntityIdentifierToRemove] = invalidIndex;

			dense.pop_back();
			indexToEntity.pop_back();
		}

		[[nodiscard]] inline const std::vector<T>& getDenseArray() { return dense; }
		const std::vector<EntityID>& getEntities() const noexcept override { return indexToEntity; }

	protected:
	private:
		static constexpr size_t invalidIndex = std::numeric_limits<size_t>::max();

		std::vector<T> dense;
		std::vector<EntityID> indexToEntity;
		std::vector<size_t> entityToIndex;
	};
}