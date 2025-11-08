#pragma once

#include <memory>

namespace ECS_System
{
	class IdentifierGenerator
	{
	public:

		static inline [[nodiscard]] std::unique_ptr<IdentifierGenerator> getInstance();
	protected:
	private:
	};
}