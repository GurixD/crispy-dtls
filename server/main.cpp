#include "Server.hpp"

void onConnected();
void onMessage();
void onDisconnected();

int main()
{

	constexpr int port = 23232;

	crispy::Server server(onConnected, onMessage, onDisconnected);
	server.start(port);

	return 0;
}


void onConnected()
{
}

void onMessage()
{
}

void onDisconnected()
{
}
