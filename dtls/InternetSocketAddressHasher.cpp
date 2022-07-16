#include "InternetSocketAddressHasher.hpp"

namespace crispy
{
	/*std::size_t h{};

	switch (isa.ss.ss_family)
	{
	case AF_INET:
	{
		const sockaddr_in* in = reinterpret_cast<const sockaddr_in*>(&isa.ss);

		unsigned short port = in->sin_port;
		unsigned long address = in->sin_addr.s_addr;

		h = std::hash<unsigned short>{}(port);
		boost::hash_combine(h, address);

		break;
	}

	case AF_INET6:
	{

		const sockaddr_in6* in6 = reinterpret_cast<const sockaddr_in6*>(&isa.ss);

		unsigned short port = in6->sin6_port;

		const unsigned char* address = in6->sin6_addr.s6_addr;
		int size = sizeof(in6->sin6_addr.s6_addr);


		h = std::hash<unsigned short>{}(port);
		for (int i = 0; i < size; ++i)
		{
			boost::hash_combine(h, address[i]);
		}

		break;
	}
	}


	return h;*/
}