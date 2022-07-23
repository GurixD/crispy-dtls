#pragma once

#include "socketstuff.h"
#include <cstring>

namespace crispy
{
	struct InternetSocketAddress
	{
		sockaddr_storage ss;

		bool operator==(const InternetSocketAddress& other) const;
	};
}