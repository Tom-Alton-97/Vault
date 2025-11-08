#pragma once

#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <vector>
#include <string>

//need a base class of type T to be able to call AsString

//can we assign a typename in anon namespace to use for 

template<typename TT>
class IndividualVaultEnum
{
public:
	[[nodiscard]] std::string_view AsString() noexcept
	{
		//how can we use reflection to cast T to a string
		std::string_view sv = __FUNCSIG__;
		auto start = sv.find("value = ") + 4; //need to add a utility to abstract 4 as an offset
		auto end = sv.rfind(">(void)", sv.end()); //this might have to be a sv.find("]", start);

		sv = sv.substr(start, end - start);

		if (auto pos = sv.find("::"); pos != std::string_view::npos)
		{
			sv.remove_prefix(pos + 2);
		}

		return sv;
	}

	//static const [[nodiscard]] std::uint_least64_t AsInt() noexcept
	//{

	//}
};

// need to write tests for this class
template<typename T>
class VaultEnum
{
	static_assert(std::is_integral_v<T>, "VaultEnum must be constructed with an integral type");

public:
	template<typename... Args>
	explicit VaultEnum(Args... args)
	{
		
		numElements = sizeof...(Args);

		//need a function to handle iterating args
			//count and save as strings
			//this may need to keep a map of the id and the string
		//assert the type of args as a 
		//iterate over args to to get num elements
		//convert item to string 
	}

	const [[nodiscard]] T Count() const noexcept
	{
		return numElements;
	}

private:

	T numElements{ 0 };
	const std::vector<std::string> elementsAsStrings{};
};