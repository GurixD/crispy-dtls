#include "Helper.hpp"

#include "Platform.h"
#include "socketstuff.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>


namespace crispy
{
	std::string Helper::byteArrayToString(std::byte* arr, std::size_t size)
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
}