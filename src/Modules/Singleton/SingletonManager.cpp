#include <ranges>

#include "SingletonManager.h"

void SingletonManager::DestroyAll() noexcept
{
	for (const auto& localDestructor : std::views::reverse(destructors))
	{
		localDestructor();
	}

	destructors.clear();
}

void SingletonManager::RegisterSingletonDestructor(std::function<void()> argDestructor) noexcept
{
	destructors.push_back(std::move(argDestructor));
}

SingletonManager::~SingletonManager()
{
	DestroyAll();
}
