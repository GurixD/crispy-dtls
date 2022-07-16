#pragma once

#include "Platform.h"

#ifdef PLATFORM_WINDOWS
#include <WinSock2.h>
#include <ws2ipdef.h>
#elif defined PLATFORM_LINUX
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include <cstring>

struct InternetSocketAddress
{
	sockaddr_storage ss;

	// TODO cpp file (maybe not?)
	bool operator==(const InternetSocketAddress& other) const
	{
		if (ss.ss_family != other.ss.ss_family)
			return false;

		switch (ss.ss_family)
		{
		case AF_INET:
		{
			const sockaddr_in* this_ss = reinterpret_cast<const sockaddr_in*>(&ss);
			const sockaddr_in* other_ss = reinterpret_cast<const sockaddr_in*>(&other.ss);

			if (this_ss->sin_port != other_ss->sin_port)
				return false;

			if (this_ss->sin_addr.s_addr != other_ss->sin_addr.s_addr)
				return false;

			return true;

			break;
		}

		case AF_INET6:
		{
			const sockaddr_in6* this_ss = reinterpret_cast<const sockaddr_in6*>(&ss);
			const sockaddr_in6* other_ss = reinterpret_cast<const sockaddr_in6*>(&other.ss);

			if (this_ss->sin6_port != other_ss->sin6_port)
				return false;

			if (std::memcmp(this_ss->sin6_addr.s6_addr, other_ss->sin6_addr.s6_addr, sizeof(this_ss->sin6_addr.s6_addr)) != 0)
				return false;

			return true;
			break;
		}

		default:
			// Only for in and in6, false for the rest
			return false;
			break;
		}
	}
};