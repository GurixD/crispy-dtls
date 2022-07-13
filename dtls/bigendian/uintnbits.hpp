#pragma once

#include <cstdint>
#include <cstring>
#include <bit>
#include "Endian.hpp"
#include "integer_concept.hpp"
#include <type_traits>
#include <concepts>
#include <iostream>

namespace bigendian 
{

	template<std::size_t Bits> requires (Bits % 8 == 0 && Bits >= 16)
	class uintnbits
	{
	private:
		std::byte data[Bits / 8];

	public:
		uintnbits()
		{
			std::memset(data, 0, sizeof(data));
		}


		template<Integer T> requires (sizeof(T) >= sizeof(data))
		uintnbits(T x = 0)
		{
			constexpr std::size_t  diff = sizeof(T) - sizeof(data);

			if constexpr (Endian::isLittleEndian())
			{
				x = std::byteswap(x);
			}

			std::memcpy(data, reinterpret_cast<std::byte*>(&x) + diff, sizeof(data));
		}

		uintnbits(const uintnbits<Bits>& x)
		{
			std::memcpy(data, x.data, sizeof(data));
		}

		template<Integer T> requires (sizeof(T) >= sizeof(data))
		T get()
		{
			T x = 0;

			constexpr std::size_t  diff = sizeof(T) - sizeof(data);

			std::memcpy(reinterpret_cast<std::byte*>(&x) + diff, &data, sizeof(data));
			if constexpr (Endian::isLittleEndian())
			{
				x = std::byteswap(x);
			}

			return x;
		}
	};

	using uint24 = bigendian::uintnbits<24>;
	using uint48 = bigendian::uintnbits<48>;
}

