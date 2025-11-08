#pragma once

#include <vector>
#include <functional>

#include "Singleton.h"

class SingletonManager
{
public:
	
	//does this need to be consteval
	static inline [[nodiscard]] std::unique_ptr<SingletonManager> getInstance() noexcept
	{
		static std::unique_ptr<SingletonManager> instance = std::make_unique<SingletonManager>(SingletonManager()); //this may need to be new

		return instance;
	}

	void RegisterSingletonDestructor(std::function<void()> argDestructor) noexcept;

protected:

	void destructor() noexcept;
private:

	void DestroyAll() noexcept;
	std::vector<std::function<void()>> destructors;
};