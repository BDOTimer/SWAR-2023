#ifndef SERVER_H
#define SERVER_H
///----------------------------------------------------------------------------|
/// "_server.h"
///----------------------------------------------------------------------------:

#include "_mysfml.h"
#include "_mess.h"

struct  Server   : protected Mess
{       Server() : Mess("CLIENT")
        {
            Account account;

            data_out =
            {   account,
                777,
                L"Hi, I'm the server",
                Data::E_READY
            };

            packet_out << data_out;

            switch ( cfg::TRANSPORT_MODE )
            {   case cfg::TRANSPORT_STRING: test_string();
                case cfg::TRANSPORT_PACKET: test_packet();
            }
        }

    unsigned short port = cfg::PORT;

    Data         data_out;
    sf::Packet packet_out;

    void test_string()
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
                      << out
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
                      << in
                      << "\"" << std::endl;
        }
    }

    void test_packet()
    {
            ///-------------------------------|
            /// Create a server socket        |
            /// to accept new connections.    |
            ///-------------------------------:
            sf::TcpListener listener;

            if (listener.listen(port) != sf::Socket::Done)
            {   info_err(L"sf::Socket::Done is FALSE");
                return;
            }

        while(true)
        {
            if(!cfg::isSERVER_SILENT)
            {   std::cout << "Server is listening to port "  << port
                          << ", waiting for connections... \n";
            }

            ///-------------------------------|
            /// Wait for a connection.        |
            ///-------------------------------:
            sf::TcpSocket socket;
            selector.add(socket);

            if (listener.accept(socket) != sf::Socket::Done)
            {   info_err(L"sf::Socket::Done is FALSE");
                return;
            }

            if(!cfg::isSERVER_SILENT)
            {   std::cout << "Client connected: "
                          << socket.getRemoteAddress() << std::endl;
            }

            ///-------------------------------|
            /// Send a message                |
            /// to the connected client.      |
            ///-------------------------------:
            if (socket.send(packet_out) != sf::Socket::Done)
            {   info_err(L"sf::Socket::Done is FALSE");
                return;
            }
            else info_out(data_out);

            ///-------------------------------|
            /// Receive a message             |
            /// from the connected client.    |
            ///-------------------------------:
            sf::Packet packet;
            if (socket.receive(packet) != sf::Socket::Done)
            {   info_err(L"sf::Socket::Done is FALSE");
                return;
            }
            else
            {   Data data; packet >> data; info_in(data);
            }

            //throw ERROR_EXCEPTION;
        }
    }

private:
    void add_sock(const sf::TcpSocket* socket)
    {
    }

    sf::SocketSelector      selector;
    std::vector<sf::TcpSocket> cargo;
};

inline void testclass_Server()
{   std::cout << __FUNCTION__ << '\n';

    if(cfg::isSERVER_SILENT)
    {   std::cout << "SERVER_SILENT == true\n";
    }

    win::set_window_name("Server");

    try
    {   Server server;
    }
    catch(const CustomException& err)
    {   std::cout  << err.what() << '\n';
    }

    std::cout << "Server FINISHED\n";
    std::cin.get();
}

#endif // SERVER_H

