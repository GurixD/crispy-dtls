#pragma once

#include <cstdint>
#include <algorithm>
#include <cstring>
#include <string>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.1
// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.5

namespace crispy
{
	struct CipherSuite
	{
		std::uint8_t cipher_suite[2];
		//  = \{ 0x[\da-zA-Z]{2}\,0x[\da-zA-Z]{2} \}
		static const CipherSuite TLS_NULL_WITH_NULL_NULL;
		static const CipherSuite TLS_RSA_WITH_NULL_MD5;
		static const CipherSuite TLS_RSA_WITH_NULL_SHA;
		static const CipherSuite TLS_RSA_WITH_NULL_SHA256;
		static const CipherSuite TLS_RSA_WITH_RC4_128_MD5;
		static const CipherSuite TLS_RSA_WITH_RC4_128_SHA;
		static const CipherSuite TLS_RSA_WITH_3DES_EDE_CBC_SHA;
		static const CipherSuite TLS_RSA_WITH_AES_128_CBC_SHA;
		static const CipherSuite TLS_RSA_WITH_AES_256_CBC_SHA;
		static const CipherSuite TLS_RSA_WITH_AES_128_CBC_SHA256;
		static const CipherSuite TLS_RSA_WITH_AES_256_CBC_SHA256;
		static const CipherSuite TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA;
		static const CipherSuite TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA;
		static const CipherSuite TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA;
		static const CipherSuite TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA;
		static const CipherSuite TLS_DH_DSS_WITH_AES_128_CBC_SHA;
		static const CipherSuite TLS_DH_RSA_WITH_AES_128_CBC_SHA;
		static const CipherSuite TLS_DHE_DSS_WITH_AES_128_CBC_SHA;
		static const CipherSuite TLS_DHE_RSA_WITH_AES_128_CBC_SHA;
		static const CipherSuite TLS_DH_DSS_WITH_AES_256_CBC_SHA;
		static const CipherSuite TLS_DH_RSA_WITH_AES_256_CBC_SHA;
		static const CipherSuite TLS_DHE_DSS_WITH_AES_256_CBC_SHA;
		static const CipherSuite TLS_DHE_RSA_WITH_AES_256_CBC_SHA;
		static const CipherSuite TLS_DH_DSS_WITH_AES_128_CBC_SHA256;
		static const CipherSuite TLS_DH_RSA_WITH_AES_128_CBC_SHA256;
		static const CipherSuite TLS_DHE_DSS_WITH_AES_128_CBC_SHA256;
		static const CipherSuite TLS_DHE_RSA_WITH_AES_128_CBC_SHA256;
		static const CipherSuite TLS_DH_DSS_WITH_AES_256_CBC_SHA256;
		static const CipherSuite TLS_DH_RSA_WITH_AES_256_CBC_SHA256;
		static const CipherSuite TLS_DHE_DSS_WITH_AES_256_CBC_SHA256;
		static const CipherSuite TLS_DHE_RSA_WITH_AES_256_CBC_SHA256;
		static const CipherSuite TLS_DH_anon_WITH_RC4_128_MD5;
		static const CipherSuite TLS_DH_anon_WITH_3DES_EDE_CBC_SHA;
		static const CipherSuite TLS_DH_anon_WITH_AES_128_CBC_SHA;
		static const CipherSuite TLS_DH_anon_WITH_AES_256_CBC_SHA;
		static const CipherSuite TLS_DH_anon_WITH_AES_128_CBC_SHA256;
		static const CipherSuite TLS_DH_anon_WITH_AES_256_CBC_SHA256;

		static const CipherSuite SupportedCipherSuites[];
		static constexpr bool isSupported(CipherSuite cipherSuite);

		std::string toString() const;
	};
}