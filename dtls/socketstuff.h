#pragma once

#include "Platform.h"


#ifdef PLATFORM_WINDOWS
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

#elif defined PLATFORM_LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <stddef.h>
#include <poll.h>
#endif

#include "Types.h"



#define PORT 23232