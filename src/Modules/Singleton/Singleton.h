#pragma once

#include <memory>
#include <mutex>

#include "SingletonManager.h"
#include "SingletonBase.h"

template <typename T>
class Singleton : public SingletonBase
{
public:

	static [[nodiscard]] T& getInstance() noexcept
	{
		static T* instanceRef = nullptr;
		static std::unique_ptr<T> instance;
		static std::once_flag initFlag;

		std::call_once(initFlag, []()
			{
				instance.reset(new T());
				instanceRef = instance.get();

				SingletonManager::getInstance()->RegisterSingleton(std::move(instance));
				SingletonManager::getInstance()->RegisterSingletonDestructor([&]()
					{
						instanceRef->destructor();
					});
			});
		
		return *instanceRef;
	}

protected:

	virtual void destructor() noexcept = 0;
private:
};