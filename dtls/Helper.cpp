#include "Helper.hpp"

#include "Platform.h"
#include "socketstuff.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cstdint>


namespace crispy
{
	std::string Helper::byteArrayToString(const std::byte* arr, std::size_t size)
	{
		std::ostringstream oss;
		oss << std::hex;

		for(std::size_t i = 0; i < size; ++i)
		{
			oss << std::setfill('0') << std::setw(2) << static_cast<std::uint16_t>(arr[i]) << " ";
		}

		oss << std::endl;

		return oss.str();
	}

	void Helper::error(std::string message)
	{
		std::cerr << message << std::endl;
		exit(1);
	}

	std::string Helper::socketError()
	{
#ifdef PLATFORM_WINDOWS
		// https://stackoverflow.com/a/46104456

		char errorMsg[256];
		int error = WSAGetLastError();

		int ret = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,   // flags
			nullptr,                // lpsource
			error,                 // message id
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),    // languageid
			errorMsg,              // output buffer
			sizeof(errorMsg),     // size of msgbuf, bytes
			nullptr);

		if (ret == 0)
		{
			return "Failed to get string from error, socket error: " + std::to_string(error) + ", FormatMessage error: " + std::to_string(WSAGetLastError());
		}
		else
		{
			return "Socket error: " + std::to_string(error) + ", " + errorMsg;
		}

#elif defined PLATFORM_LINUX
		return strerror(errno);
#endif
	}

	void Helper::printSocketError(std::string message)
	{
		error(message + socketError());
	}

	AddrInfo Helper::getAddrPort(sockaddr_storage ss)
	{
		AddrInfo addrinfo{};

		switch (ss.ss_family)
		{
		case AF_INET:
		{
			const sockaddr_in* in = reinterpret_cast<const sockaddr_in*>(&ss);

			addrinfo.port = in->sin_port;
			addrinfo.address.size = sizeof(in->sin_addr.s_addr);
			std::uint32_t address = in->sin_addr.s_addr;

			std::memcpy(addrinfo.address.data, &address, addrinfo.address.size);

			break;
		}

		case AF_INET6:
		{

			const sockaddr_in6* in6 = reinterpret_cast<const sockaddr_in6*>(&ss);

			addrinfo.port = in6->sin6_port;
			addrinfo.address.size = sizeof(in6->sin6_addr.s6_addr);

			const std::byte* address = reinterpret_cast<const std::byte*>(in6->sin6_addr.s6_addr);

			std::memcpy(addrinfo.address.data, address, addrinfo.address.size);

			break;
		}
		}

		return addrinfo;
	}
}