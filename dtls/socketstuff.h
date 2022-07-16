#pragma once

#include "Platform.h"

#ifdef PLATFORM_WINDOWS
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

using Socket = SOCKET;
#define closeSocket(s) closesocket((s))

#elif defined PLATFORM_LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

constexpr int INVALID_SOCKET = -1;
constexpr int SOCKET_ERROR = -1;

using Socket = int;

//constexpr int INVALID_SOCKET = -1;
//constexpr int SOCKET_ERROR = -1;

#define closeSocket(s) ::close(s)
#endif