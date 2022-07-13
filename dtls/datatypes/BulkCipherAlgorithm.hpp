#pragma once

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.6

namespace dtls
{
	enum class BulkCipherAlgorithm
	{
		null,
		rc4,
		_3des, // can't start with 3
		aes
	};
}