#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.1

namespace crispy
{
	struct SessionID
	{
		std::uint8_t session_id_length; // <0..32>
		std::vector<std::byte> session_id;

		std::string toString() const;
	};
}