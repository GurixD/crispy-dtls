#include "SessionID.hpp"

#include "../Helper.hpp"
#include <sstream>

namespace crispy
{
	std::string SessionID::toString() const
	{
		std::ostringstream oss;
		oss << "SessionID: " << std::endl;
		oss << "\tSession id length: " << static_cast<std::uint32_t>(this->session_id_length) << std::endl;
		oss << "\tSession id: " << Helper::byteArrayToString(this->session_id.data(), this->session_id.size()) << std::endl;
		return oss.str();
	}
}