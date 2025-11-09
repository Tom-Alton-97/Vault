#pragma once

#include <vector>
#include <functional>

#include "Singleton.h"

class SingletonManager
{
public:
	
	static inline [[nodiscard]] std::unique_ptr<SingletonManager>& getInstance() noexcept
	{
		static std::unique_ptr<SingletonManager> instance{ new SingletonManager() };

		return instance;
	}

	void RegisterSingletonDestructor(std::function<void()> argDestructor) noexcept;

protected:

private:

	friend struct std::default_delete<SingletonManager>;

	SingletonManager() = default;
	~SingletonManager();
	SingletonManager(const SingletonManager& argOther) = delete;
	SingletonManager(SingletonManager&& argOther) = delete;
	SingletonManager& operator=(const SingletonManager& argOther) = delete;
	SingletonManager& operator=(const SingletonManager&& argOther) = delete;

	void DestroyAll() noexcept;
	std::vector<std::function<void()>> destructors;
};