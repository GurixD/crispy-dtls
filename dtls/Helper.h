#pragma once

#include <string>
#include <iostream>
#include <cstddef>
#include <iomanip>

namespace dtls
{
	class Helper
	{
	public:
		/// <summary>
		/// Display an error and exit
		/// </summary>
		/// <param name="message">Message to display</param>
		static void error(std::string message);
		static std::string byteArrayToString(std::byte* arr, std::size_t size);
	};

	inline void error(std::string message)	
	{
		std::cerr << message << std::endl;

		exit(1);
	}

	inline static std::string byteArrayToString(std::byte* arr, std::size_t size)
	{
		std::ostringstream oss;
		oss << std::hex;

		for(std::size_t i = 0; i < size; ++i)
		{
			oss << std::setfill('0') << std::setw(2) << static_cast<std::uint16_t>(b) << " ";
		}

		oss << std::endl;

		return oss.str();
	}
}