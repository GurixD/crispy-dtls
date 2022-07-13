#pragma once

#include <cstdint>
#include <cstring>
#include <bit>
#include "Endian.hpp"
#include "integer_concept.hpp"
#include <type_traits>
#include <concepts>

namespace bigendian {

	template<Integer T>
	class integer
	{
	private:
		T data;

		T convert(T x) const
		{
			if constexpr (Endian::isLittleEndian())
			{
				return std::byteswap(x);
			}
			else
			{
				return x;
			}
		}

	public:
		integer(T x = 0)
		{
			data = convert(x);
		}

		integer(const integer<T>& x) : integer(x.get())
		{ }

		T get() const
		{
			return convert(data);
		}

		integer<T> operator=(const integer<T>& rhs)
		{
			data = rhs.data;
			return *this;
		}

		friend bool operator==(const integer<T>& lhs, const integer<T>& rhs)
		{
			return lhs.data == rhs.data;
		}
	};

	using uint16 = integer<std::uint16_t>;
	using uint32 = integer<std::uint32_t>;
	using uint64 = integer<std::uint64_t>;
}