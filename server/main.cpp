#include "socketstuff.h"
#include "InternetSocketAddress.hpp"
#include "InternetSocketAddressHasher.hpp"
#include <unordered_map>
#include <cstddef>
#include "DataReader.hpp"
#include "dtls/SecurityParameters.hpp"
#include "dtls/ClientHello.hpp"
#include "dtls/Handshake.hpp"
#include "dtls/DTLSPlainText.hpp"
#include "dtls/GenericBlockCipher.hpp"
#include "dtls/ContentType.hpp"
#include "dtls/Handshake.hpp"
#include "dtls/Extension.hpp"

enum class State
{
	Handshake,
	Conected
};

struct ClientData
{
	SecurityParameters sec;
	State state;
};


constexpr int MIN_MTU_IPV4 = 576;
constexpr int IPV4_HEADER_SIZE = 40;
constexpr int UDP_HEADER_SIZE = 8;
constexpr int MAX_PAYLOAD_SIZE = MIN_MTU_IPV4 - IPV4_HEADER_SIZE - UDP_HEADER_SIZE;

using Clients = std::unordered_map<InternetSocketAddress, ClientData, InternetSocketAddressHasher>;

void error(const char* message);
void verifyClient(InternetSocketAddress& from, int fromlen, DataReader& dr, Clients& clients);

int main()
{
#ifdef PLATFORM_WINDOWS
	WSAData wsaData;
	(void)WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	SOCKET fd = socket(AF_INET, SOCK_DGRAM, 0);

	sockaddr_in in{};
	in.sin_addr.s_addr = htonl(INADDR_ANY);
	in.sin_port = htons(23232);
	in.sin_family = AF_INET;
	
	bind(fd, (sockaddr*)&in, sizeof(in));


	Clients clients;
	std::byte buffer[(1 << 13) + 2048];
	bool running = true;
	while (running)
	{
		InternetSocketAddress from{};
		int fromlen = sizeof(from.ss);
		int nBytes = recvfrom(fd, reinterpret_cast<char*>(buffer), sizeof(buffer), 0, reinterpret_cast<sockaddr*>(&from.ss), &fromlen);

		DataReader dr(buffer, nBytes);

		auto search = clients.find(from);
		if (search != clients.end())
		{
			std::cout << "Old client message" << std::endl;
		}
		else
		{
			std::cout << "New client message" << std::endl;
			verifyClient(from, fromlen, dr, clients);
		}

		running = false;
	}


#ifdef PLATFORM_WINDOWS
	WSACleanup();
#endif
	return 0;
}

void error(const char* message)
{
	std::cerr << message << std::endl;
	exit(1);
}

void verifyClient(InternetSocketAddress& from, int fromlen, DataReader& dr, Clients& clients)
{
	//DTLSCiphertext<GenericBlockCipher> cipher;
	//cipher.type = static_cast<ContentType>(dr.read<std::uint8_t>());
	//cipher.version.major = dr.read<std::uint8_t>();
	//cipher.version.minor = dr.read<std::uint8_t>();
	//cipher.epoch = dr.read<bigendian::uint16>();
	//cipher.sequence_number = dr.read<bigendian::uint48>();
	//cipher.length = dr.read<bigendian::uint16>();

	// Should only receive ClientHello here

	SecurityParameters sp{ ConnectionEnd::server, CipherType::block };

	while (dr.left() > 0)
	{
		auto [dtlspt, ok] = DTLSPlaintext::fromData(dr);
		if (!ok)
			dtls::Helper::error("DTLSPlaintext from data failed");
		else
			std::cout << dtlspt.toString() << std::endl;

		if(dtlspt.type != ContentType::handshake)
			dtls::Helper::error("Type isnt handshake failed");

		
		//ContentType type = static_cast<ContentType>(dr.read<std::uint8_t>());
		//if (type != ContentType::handshake)
		//	dtls::Helper::error("Type must be handshake for new clients");

		//ProtocolVersion pv{};
		//pv.major = dr.read<std::uint8_t>();
		//pv.minor = dr.read<std::uint8_t>();
		//if(pv != ProtocolVersion::DTLS1_0)
		//	dtls::Helper::error("Version must be 1.0 for new clients");
		//
		//bigendian::uint16 epoch = dr.read<bigendian::uint16>();
		//if(epoch.get() != 0)
		//	dtls::Helper::error("Epoch must be 0 for new clients");

		//std::uint64_t seqNumber = dr.read<bigendian::uint48>().get<std::uint64_t>();
		////if(seqNumber != 0 && seqNumber != 1)
		////	dtls::Helper::error("Sequence number must be 0 or 1 for new clients");

		//bigendian::uint16 handshakeLen = dr.read<bigendian::uint16>();
		//if(handshakeLen.get() < ClientHello::minSize())
		//	dtls::Helper::error("Length is not enough for HelloClient for new clients");

		//HandshakeType handshakeType = static_cast<HandshakeType>(dr.read<std::uint8_t>());
		//if(handshakeType != HandshakeType::client_hello)
		//	dtls::Helper::error("HandshakeType must be HelloClient for new clients");

	}
}