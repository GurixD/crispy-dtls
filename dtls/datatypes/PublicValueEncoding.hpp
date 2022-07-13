#pragma once

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.3

namespace dtls
{
	enum class PublicValueEncoding
	{
		implicit,
		explicit_ // "explicit" is a key word
	};
}