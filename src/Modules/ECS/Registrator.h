#pragma once

namespace ECS_System
{
	class Registrator
	{
	public:

		static inline [[nodiscard]] Registrator& getInstance() noexcept
		{
			static Registrator instance;

			return instance;
		}


		void createEntity() {};
		void createComponent() {};
		void createSystem() {};
		
		void registerComponent() {};
		void registerSystem() {};

	protected:
	private:
	};
}