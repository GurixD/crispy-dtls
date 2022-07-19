#pragma once

#include <string>
#include <cstddef>
#include <functional>

namespace crispy
{
	class Helper
	{
	public:
		/// <summary>
		/// Display an error and exit
		/// </summary>
		/// <param name="message">Message to display</param>
		static std::string byteArrayToString(const std::byte* arr, std::size_t size);
		static std::string socketError();
		static void error(std::string message);
		static void printSocketError(std::string message);

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