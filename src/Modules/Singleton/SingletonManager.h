#pragma once

#include <vector>
#include <functional>
#include <memory>

#include "SingletonBase.h"

class SingletonManager
{
public:
	
	static inline [[nodiscard]] std::unique_ptr<SingletonManager>& getInstance() noexcept
	{
		static std::unique_ptr<SingletonManager> instance{ new SingletonManager() };

		return instance;
	}

	void RegisterSingleton(std::unique_ptr<SingletonBase> argSingletonToRegister) noexcept;
	void RegisterSingletonDestructor(std::function<void()> argDestructor) noexcept;
	void DeleteSingleton(SingletonBase* argSingletonToDestroy) noexcept;

	std::vector<std::unique_ptr<SingletonBase>> singletons;
	std::vector<std::function<void()>> destructors;

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
};