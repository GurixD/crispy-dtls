#pragma once

#include "InternetSocketAddress.hpp"
#include "Helper.hpp"
#include <functional>
#include <cstddef>

namespace crispy
{
	struct InternetSocketAddressHasher
	{
		std::size_t operator()(const InternetSocketAddress& isa) const;
	};
}