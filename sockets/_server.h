#ifndef HEADER_F2B622319B3E16ED
#define HEADER_F2B622319B3E16ED

///----------------------------------------------------------------------------|
/// "_server.h"
///----------------------------------------------------------------------------:
#ifndef SERVER_H
#define SERVER_H

#include "_mysfml.h"

struct  Server
{       Server() : ATRBin (win::convert(11, 0)),
                   ATRBout(win::convert(12, 0))
        {
            switch ( cfg::TRANSPORT_MODE )
            {   case cfg::TRANSPORT_STRING: test_01();
                case cfg::TRANSPORT_PACKET: test_02();
            }
        }

    unsigned short port = cfg::PORT;

    const short ATRBin ;
    const short ATRBout;

    void test_01()
    {
        while(true)
        {
            ///-------------------------------|
            /// Create a server socket        |
            /// to accept new connections.    |
            ///-------------------------------:
            sf::TcpListener listener;

            if (listener.listen(port) != sf::Socket::Done) return;

            std::cout << "Server is listening to port "  << port
                      << ", waiting for connections... \n";

            ///-------------------------------|
            /// Wait for a connection.        |
            ///-------------------------------:
            sf::TcpSocket socket;
            if (listener.accept(socket) != sf::Socket::Done) return;

            std::cout << "Client connected: "
                      << socket.getRemoteAddress() << std::endl;

            ///-------------------------------|
            /// Send a message                |
            /// to the connected client.      |
            ///-------------------------------:
            const char out[] = "Hi, I'm the server";
            if (socket.send(out, sizeof(out)) != sf::Socket::Done) return;
            std::cout << "Message sent to the client: \""
                      << win::Screen::color_str(out, ATRBout)
                      << "\"" << std::endl;

            ///-------------------------------|
            /// Receive a message             |
            /// to the connected client.      |
            ///-------------------------------:
            char in[128];
            std::size_t received;
            if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
                return;
            std::cout << "Answer received from the client: \""
                      << win::Screen::color_str(in, ATRBin)
                      << "\"" << std::endl;
        }
    }

    void test_02()
    {
        while(true)
        {
            ///-------------------------------|
            /// Create a server socket        |
            /// to accept new connections.    |
            ///-------------------------------:
            sf::TcpListener listener;

            if (listener.listen(port) != sf::Socket::Done) return;

            std::cout << "Server is listening to port "  << port
                      << ", waiting for connections... \n";

            ///-------------------------------|
            /// Wait for a connection.        |
            ///-------------------------------:
            sf::TcpSocket socket;
            if (listener.accept(socket) != sf::Socket::Done) return;

            std::cout << "Client connected: "
                      << socket.getRemoteAddress() << std::endl;

            ///-------------------------------|
            /// Send a message                |
            /// to the connected client.      |
            ///-------------------------------:
            const char out[] = "Hi, I'm the server";
            if (socket.send(out, sizeof(out)) != sf::Socket::Done) return;
            std::cout << "Message sent to the client: \""
                      << win::Screen::color_str(out, ATRBout)
                      << "\"" << std::endl;

            ///-------------------------------|
            /// Receive a message             |
            /// to the connected client.      |
            ///-------------------------------:
            sf::Packet packet;
            if (socket.receive(packet) != sf::Socket::Done)
                return;
            Data data; packet >> data;
            std::wcout << "Answer received from the client: \""
                       << win::Screen::color(ATRBin) << data
                       << win::Screen::color()
                       << "\"" << std::endl;
        }
    }
};

inline void testclass_Server()
{   std::cout << __FUNCTION__ << '\n';
    win::set_window_name("Server");

    Server server;

    std::cout << "Server FINISHED\n";
    std::cin.get();
}

#endif // SERVER_H
#endif // header guard

