#pragma once

#include <string>
#include <cstddef>
#include <functional>
#include <tuple>
#include "socketstuff.h"
#include "AddrInfo.hpp"

namespace crispy
{
	class Helper
	{
	public:
		/// <summary>
		/// Convert data as byte* format to string
		/// </summary>
		static std::string byteArrayToString(const std::byte* arr, std::size_t size);

		/// <summary>
		/// Get the string of the last socket error (WSAGetLastError / errno)
		/// </summary>
		static std::string socketError();

		/// <summary>
		/// Print to cerr and exit
		/// </summary>
		/// <param name="message">Message to print</param>
		static void error(std::string message);

		/// <summary>
		/// Litteraly error(message + socketError());
		/// </summary>
		/// <param name="message">Message to print</param>
		static void printSocketError(std::string message);

		/// <summary>
		/// Return information of inet/inet6 form sockaddr_storage
		/// </summary>
		/// <param name="ss">Storage to get info from</param>
		/// <returns>[Data containing address, size of data, port]</returns>
		static AddrInfo getAddrPort(sockaddr_storage ss);

		/// <summary>
		/// Combine hash like boost
		/// </summary>
		/// <param name="seed">Current hash</param>
		/// <param name="v"></param>
		template <typename T>
		static void hashCombine(std::size_t& seed, const T& v);
	};

	template<typename T>
	inline void Helper::hashCombine(std::size_t& seed, const T& v)
	{
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
}