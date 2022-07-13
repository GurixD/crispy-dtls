#pragma once

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.6

namespace dtls
{
	enum class CipherType
	{
		stream,
		block,
		aead
	};
}