#pragma once

#include <unordered_map>

#include"EntityManager.h"
#include "SystemBase.h"
#include <typeindex>

namespace ECS_System
{
	class SystemManager : public Singleton<SystemManager>
	{
	public:
		template <typename T, typename... Args>
		T& registerSystem(Args&&... args)
		{
			const std::type_index type = typeid(T);

			auto iterator = systems.find(type);
			
			if (iterator != systems.end())
			{
				return *static_cast<T*>(iterator->second.get());
			}

			auto sys = std::make_unique<T>(std::forward<Args>(args)...);
			T* sysPtr = sys.get();
			systems.emplace(type, std::move(sys));
			return *sysPtr;
		}

		void updateSystems(const float argDeltaTime)
		{
			for (auto& [_, sys] : systems)
			{
				sys->update(argDeltaTime);
			}
		}

		template <typename T>
		void updateSystem(const float argDeltaTime)
		{
			const std::type_index type = typeid(T);

			auto iterator = systems.find(type);

			if (iterator != systems.end())
			{
				iterator->second.get()->update(argDeltaTime);
			}

			// TODO log
		}

		void Reset()
		{
			systems.clear();
		}

		template <typename T>
		T* getSystem()
		{
			const std::type_index type = typeid(T);

			auto iterator = systems.find(type);

			if (iterator == systems.end())
			{
				// TODO log
				return nullptr;
			}

			return static_cast<T*>(iterator->second.get());
		}

		void destructor() noexcept override
		{
			systems.clear();
		}

	protected:
	private:

		friend struct std::default_delete<EntityManager>;
		friend class Singleton<EntityManager>;

		std::unordered_map<std::type_index, std::unique_ptr<SystemBase>> systems;
	};
}