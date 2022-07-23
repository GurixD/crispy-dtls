#pragma once

#include "socketstuff.h"
#include "AddrInfo.hpp"
#include "Array.hpp"
#include <cstddef>
#include <openssl/rand.h>
#include <openssl/hmac.h>
#include <algorithm>
#include <mutex>
#include <array>
#include <vector>
#include <iostream>


namespace crispy
{
	template<std::size_t S>
	class Cookie
	{
	private:
		std::array<std::byte, S> currentSecret;
		std::array<std::byte, S> oldSecret;
		std::mutex secretMutex;
		const EVP_MD* sha256;

		void generateSecret();
		void copySecret();

	public:
		Cookie();

		/// <summary>
		/// Place current secret in old secret and generate new secret
		/// </summary>
		void rotateCookie();

		bool verifyCookie(std::vector<std::byte> cookie, AddrInfo addrinfo);
		std::vector<std::byte> getCookie(AddrInfo addrinfo, bool usingCurrentSecret = true);
	};

	template<std::size_t S>
	inline void Cookie<S>::generateSecret()
	{
		RAND_priv_bytes(reinterpret_cast<unsigned char*>(this->currentSecret.data()), S);
	}

	template<std::size_t S>
	inline void Cookie<S>::copySecret()
	{
		std::copy(this->currentSecret.begin(), this->currentSecret.end(), this->oldSecret.begin());
	}

	template<std::size_t S>
	inline Cookie<S>::Cookie() : sha256(EVP_sha256())
	{
		generateSecret();
		copySecret();
	}

	template<std::size_t S>
	inline void Cookie<S>::rotateCookie()
	{
		std::scoped_lock lock(this->secretMutex);
		std::cout << "Rotating cookie" << std::endl;
		copySecret();
		generateSecret();
	}

	template<std::size_t S>
	inline bool Cookie<S>::verifyCookie(std::vector<std::byte> cookie, AddrInfo addrinfo)
	{
		std::vector<std::byte> currentCookie = getCookie(addrinfo);
		if (cookie == currentCookie)
			return true;

		Array<std::byte> oldCookie = getCookie(addrinfo, false);
		return cookie == oldCookie;
	}


	template<std::size_t S>
	inline std::vector<std::byte> Cookie<S>::getCookie(AddrInfo addrinfo, bool usingCurrentSecret)
	{
		std::scoped_lock lock(this->secretMutex);
		std::vector<std::byte> clientBuffer;
		
		// Add port to buffer
		Array<std::byte> portData{};
		portData.size = sizeof(addrinfo.port);
		portData.data = reinterpret_cast<std::byte*>(addrinfo.port);
		for(std::size_t i = 0; i < portData.size; ++i)
		{
			clientBuffer.push_back(portData.data[i]);
		}

		// Add address to buffer
		for(std::size_t i = 0; i < addrinfo.address.size; ++i)
		{
			clientBuffer.push_back(addrinfo.address.data[i]);
		}

		std::vector<std::byte> result;
		result.resize(EVP_MAX_MD_SIZE);
		unsigned int resultLen = sizeof(EVP_MAX_MD_SIZE);
		std::byte* secret = usingCurrentSecret ? this->currentSecret.data() : this->oldSecret.data();
		
		HMAC(this->sha256, secret, S, clientBuffer.data(), clientBuffer.size(), result, &resultLen);

		result.resize(resultLen);

		return result;
	}
}