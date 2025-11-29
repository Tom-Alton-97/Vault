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

void SingletonManager::RegisterSingleton(std::unique_ptr<SingletonBase> argSingletonToRegister) noexcept
{
	singletons.push_back(std::move(argSingletonToRegister));
}

void SingletonManager::RegisterSingletonDestructor(std::function<void()> argDestructor) noexcept
{
	destructors.push_back(std::move(argDestructor));
}

void SingletonManager::DeleteSingleton(SingletonBase* argSingletonToDestroy) noexcept
{
	auto singletonIterator = 
		std::find_if(singletons.begin(), singletons.end(), 
		[argSingletonToDestroy](const std::unique_ptr<SingletonBase>& ptr)
		{
			return ptr.get() == argSingletonToDestroy;
		});

	if (singletonIterator == singletons.end())
	{
		// TODO log 
		return;
	}

	std::size_t singletonIndex = std::distance(singletons.begin(), singletonIterator);

	std::invoke(destructors[singletonIndex]);

	destructors.erase(destructors.begin() + singletonIndex);
	singletons.erase(singletons.begin() + singletonIndex);
}

SingletonManager::~SingletonManager()
{
	DestroyAll();
}
