#pragma once

#include <functional>
#include <cstdint>
#include <unordered_map>

#include "socketstuff.h"
#include "InternetSocketAddress.hpp"
#include "InternetSocketAddressHasher.hpp"
#include "ClientData.hpp"
#include "DataReader.hpp"

namespace crispy
{
    using OnConnected = std::function<void(void)>;
    using OnMessage = std::function<void(void)>;
    using OnDisconnected = std::function<void(void)>;
    using Clients = std::unordered_map<InternetSocketAddress, ClientData, InternetSocketAddressHasher>;

    class Server
    {
    private:
        OnConnected onConnected;
        OnMessage onMessage;
        OnDisconnected onDisconnected;
        Clients clients;

        Socket fd;
        std::uint16_t port;

#ifdef PLATFORM_WINDOWS
        WSAData wsaData;
#endif


    public:
        Server(OnConnected onConnected, OnMessage onMessage, OnDisconnected onDisconnected);

        void start(std::uint16_t port);
        bool close();

    private:
        void verifyClient(InternetSocketAddress& from, int fromlen, DataReader& dr, Clients& clients);

        static constexpr int MIN_MTU_IPV4 = 576;
        static constexpr int IPV4_HEADER_SIZE = 40;
        static constexpr int UDP_HEADER_SIZE = 8;
        static constexpr int MAX_PAYLOAD_SIZE = MIN_MTU_IPV4 - IPV4_HEADER_SIZE - UDP_HEADER_SIZE;
    };
}