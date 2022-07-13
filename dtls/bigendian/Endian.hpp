#pragma once
#include <bit>

static_assert(std::endian::native == std::endian::little || std::endian::native == std::endian::big);

class Endian
{
public:
	constexpr static bool isLittleEndian()
	{
		return std::endian::native != std::endian::big;
	}
};