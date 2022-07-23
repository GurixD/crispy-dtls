#include "InternetSocketAddressHasher.hpp"

namespace crispy
{
	std::size_t InternetSocketAddressHasher::operator()(const InternetSocketAddress& isa) const
	{
		std::size_t h{};

		AddrInfo addrinfo = Helper::getAddrPort(isa.ss);

		Helper::hashCombine(h, addrinfo.port);
		for (int i = 0; i < addrinfo.address.size; ++i)
		{
			Helper::hashCombine(h, addrinfo.address.data[i]);
		}

		return h;
	}
}