#include "InternetSocketAddress.hpp"

#include "AddrInfo.hpp"
#include "Helper.hpp"

namespace crispy
{
	bool InternetSocketAddress::operator==(const InternetSocketAddress& otherAddress) const
	{
		AddrInfo that = Helper::getAddrPort(this->ss);
		AddrInfo other = Helper::getAddrPort(otherAddress.ss);

		return that == other;
	}
}