#pragma once

#include <string>
#include <cstddef>

namespace crispy
{
	class Helper
	{
	public:
		/// <summary>
		/// Display an error and exit
		/// </summary>
		/// <param name="message">Message to display</param>
		static std::string byteArrayToString(std::byte* arr, std::size_t size);
		static std::string socketError();
		static void error(std::string message);
		static void printSocketError(std::string message);
	};
}