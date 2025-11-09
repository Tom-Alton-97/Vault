#pragma once

#include <memory>

template <typename T>
class Singleton
{
public:

	virtual [[nodiscard]] std::unique_ptr<T> getInstance() noexcept = 0;

protected:

	virtual void destructor() noexcept = 0;
private:
};