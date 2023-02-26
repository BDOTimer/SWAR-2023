///----------------------------------------------------------------------------|
/// Тест SFML Sokets.
/// 	-finput-charset=CP1251
///----------------------------------------------------------------------------:
//#define UNICODE
#include <iostream>
#include <cstdlib>

#include <windows.h>

#include "TCP.h"

void runTcpClient(unsigned short port);
void runUdpServer(unsigned short port);
void runUdpClient(unsigned short port);

///----------------------------------------------------------------------------|
/// Старт.
///----------------------------------------------------------------------------:
int main()
{   setlocale(0, "");
	//LOG_ERROR(L"LOG_ERROR включен ...");

    // Choose an arbitrary port for opening sockets
    const unsigned short port = 50001;

    // TCP, UDP or connected UDP ?
    char protocol = 't';
    //std::cout << "Do you want to use TCP (t) or UDP (u)? ";
    //std::cin  >> protocol;

    std::cout << "Do you want to be a server (s) or a client (c)? ";
    char who; std::cin  >> who;

    if (protocol == 't')
    {
        // Test the TCP protocol
        if (who == 's')
        {	SetConsoleTitleW(L"TCPServer: Игра XXX.");
        	TCPServer server(port);
		}
        else
        {	SetConsoleTitleW(L"TCPClient: Игра XXX.");
			TCPClient client(port);
		}
    }
    else
    {
        // Test the unconnstd::cin.ignore(10000, '\n');ected UDP protocol
        if (who == 's')
            runUdpServer(port);
        else
            runUdpClient(port);
    }

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    
    std::cin.ignore(10000, '\n');

    return EXIT_SUCCESS;
}
