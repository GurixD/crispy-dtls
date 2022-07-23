#pragma once

#include <cstddef>
#include <cstring>

namespace crispy
{
	template <typename T>
	struct Array
	{
		T* data;
		std::size_t size;

		template <typename T>
		friend bool operator==(const Array<T>& lhs, const Array<T>& rhs);

		//template <typename T>
		//friend bool operator!=(const Array<T>& lhs, const Array<T>& rhs);
	};

	template<typename T>
	bool operator==(const Array<T>& lhs, const Array<T>& rhs)
	{
		return lhs.size == rhs.size && std::memcmp(lhs.data, rhs.data, lhs.size) == 0;
	}
}