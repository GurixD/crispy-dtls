#pragma once

#include "Platform.h"

#ifdef PLATFORM_LINUX

#include <unistd.h>

using SOCKET = int;

const int INVALID_SOCKET = -1;
const int SOCKET_ERROR = -1;

#define closesocket(s) ::close(s)

#endif