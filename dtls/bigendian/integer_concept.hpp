#pragma once

#include <concepts>
#include <type_traits>

namespace bigendian
{
	template<typename T>
	concept Integer = std::integral<T>;
}