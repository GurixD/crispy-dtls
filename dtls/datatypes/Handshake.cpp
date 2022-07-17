#include "Handshake.hpp"

#include <cstdint>
#include <tuple>
#include <sstream>

namespace crispy
{
	std::string Handshake::toString() const
	{
		std::ostringstream oss;

		oss << "Handshake: " << std::endl;
		oss << "Message type: " << static_cast<std::uint8_t>(this->msg_type) << std::endl;
		oss << "Length: " << this->length.get<std::uint32_t>() << std::endl;
		oss << "Message sequence: " << this->message_seq.get() << std::endl;
		oss << "Fragment offset: " << this->fragment_offset.get<std::uint32_t>() << std::endl;
		oss << "Fragment length: " << this->fragment_length.get<std::uint32_t>() << std::endl;
		oss << "Body: " << Helper::byteArrayToString(this->body.data(), this->body.size()) << std::endl;

		return oss.str();
	}


	std::tuple<Handshake, bool> Handshake::fromData(DataReader& dr)
	{
		Handshake handshake{};

		dr.startTransaction();

		handshake.msg_type = static_cast<HandshakeType>(dr.read<std::uint8_t>());
		handshake.length = dr.read<bigendian::uint24>();
		handshake.message_seq = dr.read<bigendian::uint16>();
		handshake.fragment_offset = dr.read<bigendian::uint24>();
		handshake.fragment_length = dr.read<bigendian::uint24>();

		dr.read(handshake.body, handshake.fragment_length.get<std::size_t>());
	
		return { handshake, dr.checkTransaction() };
	}
}