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

		inline const [[nodiscard]] ECS_System::EntityID getUnusedEntityIdentifier() noexcept
		{
			return ++NEXT_ARBITRARY_ENTITY_IDENTIFIER;
		}

	private:

		ECS_System::EntityID NEXT_ARBITRARY_ENTITY_IDENTIFIER{ 0 };
		const ECS_System::EntityActiveStatus DEFAULT_ENTITY_ACTIVE_STATUS{ ECS_System::EntityActiveStatus::EntityDisabled };

		ECS_Tests_Utility() = default;
		~ECS_Tests_Utility() = default;
		ECS_Tests_Utility(const ECS_Tests_Utility& argOther) = delete;
		ECS_Tests_Utility(ECS_Tests_Utility&& argOther) = delete;
		ECS_Tests_Utility& operator=(const ECS_Tests_Utility& argOther) = delete;
		ECS_Tests_Utility& operator=(const ECS_Tests_Utility&& argOther) = delete;
	};
}