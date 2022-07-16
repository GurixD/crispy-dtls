#include "Server.hpp"

#include <iostream>
#include "Helper.hpp"
#include "datatypes/DTLSPlaintext.hpp"
#include "datatypes/SecurityParameters.hpp"
#include <cstddef>

namespace crispy
{
	Server::Server(OnConnected onConnected, OnMessage onMessage, OnDisconnected onDisconnected) :
		onConnected(onConnected),
		onMessage(onMessage),
		onDisconnected(onDisconnected),
		fd(INVALID_SOCKET),
		port(0)
	{
#ifdef PLATFORM_WINDOWS
		std::memset(&this->wsaData, 0, sizeof(this->wsaData));
#endif 
	}

	void Server::start(std::uint16_t port)
	{
		this->port = port;


#ifdef PLATFORM_WINDOWS
		WSAData wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			Helper::printSocketError("WSAStartup failed: ");
		}
#endif

		this->fd = socket(AF_INET, SOCK_DGRAM, 0);
		if (this->fd == INVALID_SOCKET)
		{
			Helper::printSocketError("socket failed: ");
		}

		sockaddr_in in{};
		in.sin_addr.s_addr = htonl(INADDR_ANY);
		in.sin_port = htons(this->port);
		in.sin_family = AF_INET;

		if (bind(this->fd, (sockaddr*)&in, sizeof(in)) == SOCKET_ERROR)
		{
			Helper::printSocketError("bind failed: ");
		}

		std::byte buffer[(1 << 13) + 2048];
		bool running = true;
		while (running)
		{
			InternetSocketAddress from{};
			int fromlen = sizeof(from.ss);
			int nBytes = recvfrom(this->fd, reinterpret_cast<char*>(buffer), sizeof(buffer), 0, reinterpret_cast<sockaddr*>(&from.ss), &fromlen);

			DataReader dr(buffer, nBytes);

			auto search = this->clients.find(from);
			if (search != this->clients.end())
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
	}

	bool Server::close()
	{

		closeSocket(this->fd);

#ifdef PLATFORM_WINDOWS
		WSACleanup(); // TODO check return value
#endif 

		return false;
	}

	void Server::verifyClient(InternetSocketAddress& from, int fromlen, DataReader& dr, Clients& clients)
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
				Helper::error("DTLSPlaintext from data failed");
			else
				std::cout << dtlspt.toString() << std::endl;

			if (dtlspt.type != ContentType::handshake)
				Helper::error("Type isnt handshake failed");

		}
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
