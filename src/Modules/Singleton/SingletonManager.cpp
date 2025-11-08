#include "SingletonManager.h"

void SingletonManager::DestroyAll() noexcept
{
	for (const auto it = destructors.rbegin(); it != destructor.rend(); ++it)
	{
		(*it)();
	}

	destructors.clear();
}

void SingletonManager::RegisterSingletonDestructor(std::function<void()> argDestructor) noexcept
{
	destructors.push_back(std::move(argDestructor));
}

void SingletonManager::destructor() noexcept
{
	DestroyAll();
}
