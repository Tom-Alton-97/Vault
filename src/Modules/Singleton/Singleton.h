#pragma once

#include <memory>
#include <mutex>

#include "SingletonManager.h"
#include "SingletonBase.h"

template <typename T>
class Singleton : public SingletonBase
{
public:

	static inline [[nodiscard]] T& getInstance() noexcept
	{
		static T* instancePtr = nullptr;
		static std::unique_ptr<T> instance;
		static std::once_flag initFlag;

		std::call_once(initFlag, []()
			{
				instance.reset(new T());
				instancePtr = instance.get();

				SingletonManager::getInstance()->RegisterSingleton(std::move(instance));
				SingletonManager::getInstance()->RegisterSingletonDestructor([&]()
					{
						instancePtr->destructor();
						instancePtr = nullptr;
					});
			});
		
		return *instancePtr;
	}

protected:

	friend class SingletonManager;

	Singleton() = default;
	~Singleton() = default;

	virtual void destructor() noexcept = 0;
private:
};