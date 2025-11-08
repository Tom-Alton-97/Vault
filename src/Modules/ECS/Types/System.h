#pragma once

namespace ECS_System
{
	template<typename T>
	class System
	{
	public:

		virtual void update() = 0;
	protected:
	private:
	};
}