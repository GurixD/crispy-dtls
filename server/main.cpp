#include "Server.hpp"
#include "timer/Timer.hpp"
#include <iostream>
#include <functional>

void onConnected();
void onMessage();
void onDisconnected();
void print(const char* message);
void testTimer();

int main()
{
	//constexpr int port = 23232;

	//crispy::Server server(onConnected, onMessage, onDisconnected);
	//server.start(port);

	testTimer();

	return 0;
}

void testTimer()
{
	using Timer = crispy::timer::Timer;
	using namespace std::chrono_literals;
	Timer::setTimeout(std::bind(print, "Once"), 1s);
	Timer::setInterval(std::bind(print, "Always"), 2s);
	Timer::setNTimeout(std::bind(print, "Thrice"), 3s, 3);
	(void)std::getchar();
}

void print(const char* message)
{
	std::cout << message << std::endl;
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
