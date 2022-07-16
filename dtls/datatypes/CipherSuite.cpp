#include "CipherSuite.hpp"

namespace crispy
{    
    inline constexpr CipherSuite CipherSuite::TLS_NULL_WITH_NULL_NULL = {0x00, 0x00};
	inline constexpr CipherSuite CipherSuite::TLS_RSA_WITH_NULL_MD5 = {0x00, 0x01};
	inline constexpr CipherSuite CipherSuite::TLS_RSA_WITH_NULL_SHA = {0x00, 0x02};
	inline constexpr CipherSuite CipherSuite::TLS_RSA_WITH_NULL_SHA256 = {0x00, 0x3B};
	inline constexpr CipherSuite CipherSuite::TLS_RSA_WITH_RC4_128_MD5 = {0x00, 0x04};
	inline constexpr CipherSuite CipherSuite::TLS_RSA_WITH_RC4_128_SHA = {0x00, 0x05};
	inline constexpr CipherSuite CipherSuite::TLS_RSA_WITH_3DES_EDE_CBC_SHA = {0x00, 0x0A};
	inline constexpr CipherSuite CipherSuite::TLS_RSA_WITH_AES_128_CBC_SHA = {0x00, 0x2F};
	inline constexpr CipherSuite CipherSuite::TLS_RSA_WITH_AES_256_CBC_SHA = {0x00, 0x35};
	inline constexpr CipherSuite CipherSuite::TLS_RSA_WITH_AES_128_CBC_SHA256 = {0x00, 0x3C};
	inline constexpr CipherSuite CipherSuite::TLS_RSA_WITH_AES_256_CBC_SHA256 = {0x00, 0x3D};
	inline constexpr CipherSuite CipherSuite::TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA = {0x00, 0x0D};
	inline constexpr CipherSuite CipherSuite::TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA = {0x00, 0x10};
	inline constexpr CipherSuite CipherSuite::TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA = {0x00, 0x13};
	inline constexpr CipherSuite CipherSuite::TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA = {0x00, 0x16};
	inline constexpr CipherSuite CipherSuite::TLS_DH_DSS_WITH_AES_128_CBC_SHA = {0x00, 0x30};
	inline constexpr CipherSuite CipherSuite::TLS_DH_RSA_WITH_AES_128_CBC_SHA = {0x00, 0x31};
	inline constexpr CipherSuite CipherSuite::TLS_DHE_DSS_WITH_AES_128_CBC_SHA = {0x00, 0x32};
	inline constexpr CipherSuite CipherSuite::TLS_DHE_RSA_WITH_AES_128_CBC_SHA = {0x00, 0x33};
	inline constexpr CipherSuite CipherSuite::TLS_DH_DSS_WITH_AES_256_CBC_SHA = {0x00, 0x36};
	inline constexpr CipherSuite CipherSuite::TLS_DH_RSA_WITH_AES_256_CBC_SHA = {0x00, 0x37};
	inline constexpr CipherSuite CipherSuite::TLS_DHE_DSS_WITH_AES_256_CBC_SHA = {0x00, 0x38};
	inline constexpr CipherSuite CipherSuite::TLS_DHE_RSA_WITH_AES_256_CBC_SHA = {0x00, 0x39};
	inline constexpr CipherSuite CipherSuite::TLS_DH_DSS_WITH_AES_128_CBC_SHA256 = {0x00, 0x3E};
	inline constexpr CipherSuite CipherSuite::TLS_DH_RSA_WITH_AES_128_CBC_SHA256 = {0x00, 0x3F};
	inline constexpr CipherSuite CipherSuite::TLS_DHE_DSS_WITH_AES_128_CBC_SHA256 = {0x00, 0x40};
	inline constexpr CipherSuite CipherSuite::TLS_DHE_RSA_WITH_AES_128_CBC_SHA256 = {0x00, 0x67};
	inline constexpr CipherSuite CipherSuite::TLS_DH_DSS_WITH_AES_256_CBC_SHA256 = {0x00, 0x68};
	inline constexpr CipherSuite CipherSuite::TLS_DH_RSA_WITH_AES_256_CBC_SHA256 = {0x00, 0x69};
	inline constexpr CipherSuite CipherSuite::TLS_DHE_DSS_WITH_AES_256_CBC_SHA256 = {0x00, 0x6A};
	inline constexpr CipherSuite CipherSuite::TLS_DHE_RSA_WITH_AES_256_CBC_SHA256 = {0x00, 0x6B};
	inline constexpr CipherSuite CipherSuite::TLS_DH_anon_WITH_RC4_128_MD5 = {0x00, 0x18};
	inline constexpr CipherSuite CipherSuite::TLS_DH_anon_WITH_3DES_EDE_CBC_SHA = {0x00, 0x1B};
	inline constexpr CipherSuite CipherSuite::TLS_DH_anon_WITH_AES_128_CBC_SHA = {0x00, 0x34};
	inline constexpr CipherSuite CipherSuite::TLS_DH_anon_WITH_AES_256_CBC_SHA = {0x00, 0x3A};
	inline constexpr CipherSuite CipherSuite::TLS_DH_anon_WITH_AES_128_CBC_SHA256 = {0x00, 0x6C};
	inline constexpr CipherSuite CipherSuite::TLS_DH_anon_WITH_AES_256_CBC_SHA256 = {0x00, 0x6D};

	inline constexpr CipherSuite CipherSuite::SupportedCipherSuites[] = {CipherSuite::TLS_RSA_WITH_AES_128_CBC_SHA};

	inline constexpr bool CipherSuite::isSupported(CipherSuite cipherSuite)
	{
		for (auto supportedCipherSuite : SupportedCipherSuites)
		{
			if (std::memcmp(cipherSuite.cipher_suite, supportedCipherSuite.cipher_suite, sizeof(cipherSuite.cipher_suite)) == 0)
				return true;
		}

		return false;
	}
}