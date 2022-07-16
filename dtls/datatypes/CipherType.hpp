#pragma once

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.6

namespace crispy
{
	enum class CipherType
	{
		stream,
		block,
		aead
	};
}