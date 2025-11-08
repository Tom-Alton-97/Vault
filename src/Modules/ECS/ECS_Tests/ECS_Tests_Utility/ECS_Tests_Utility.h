#pragma once

#include "Entity.h"

namespace Tests_Utility
{
	class ECS_Tests_Utility
	{
	public:

		static inline [[nodiscard]] ECS_Tests_Utility& getInstance() noexcept
		{
			static ECS_Tests_Utility singletonInstance;

			return singletonInstance;
		}

		inline const [[nodiscard]] EntityID getUnusedEntityIdentifier() noexcept
		{
			return ++NEXT_ARBITRARY_ENTITY_IDENTIFIER;
		}

	private:

		EntityID NEXT_ARBITRARY_ENTITY_IDENTIFIER{ 0 };
		const EntityActiveStatus DEFAULT_ENTITY_ACTIVE_STATUS{ EntityActiveStatus::EntityDisabled };

		ECS_Tests_Utility() = default;
		~ECS_Tests_Utility() = default;
		ECS_Tests_Utility(const ECS_Tests_Utility& argOther) = delete;
		ECS_Tests_Utility(ECS_Tests_Utility&& argOther) = delete;
		ECS_Tests_Utility& operator=(const ECS_Tests_Utility& argOther) = delete;
		ECS_Tests_Utility& operator=(const ECS_Tests_Utility&& argOther) = delete;
	};
}