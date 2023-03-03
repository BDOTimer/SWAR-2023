#ifndef CLIENT_H
#define CLIENT_H
///----------------------------------------------------------------------------|
/// "_client.h"
///----------------------------------------------------------------------------:

#include "_mysfml.h"
#include "_mess.h"

struct  Client : protected Mess
{       Client(Account acc) :   Mess   ("SERVER"),
                                account(acc)
        {
            if(false == set_address(address_server)) return;

            data_out = {account, 2023, L"Привет, Мир!"};

            switch ( cfg::TRANSPORT_MODE )
            {   case cfg::TRANSPORT_STRING: test_string();
                case cfg::TRANSPORT_PACKET: test_packet();
            }
        }

    unsigned short port = cfg::PORT;
    sf::IpAddress  address_server  ;

    const Account account;
    Data         data_out;

    void test_string()
    {
        for(int i = 0; i < 3; ++i)
        {
            ///-------------------------------|
            /// Create a socket for           |
            /// communicating with the server.|
            ///-------------------------------:
            sf::TcpSocket socket;

            if (socket.connect(address_server, port) != sf::Socket::Done)
                return;
            std::cout << "Connect to the server "
                      << address_server
                      << " GOOD\n";

            ///-------------------------------|
            /// Receive a message             |
            /// from the server.              |
            ///-------------------------------:
            char in[128];
            std::size_t received;
            if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
                return;
            std::cout << "Message received from the server: \""
                      << in
                      << "\"" << std::endl;

            ///-------------------------------|
            /// Send an answer to the server. |
            ///-------------------------------:
            const char  out[] = "Hi, I'm a client ";
            std::string Out(out);
                        Out  += account.to_string();

            if (socket.send(Out.c_str(), Out.size()) != sf::Socket::Done)
                return;
            std::cout << "Message sent to the server: \""
                      << Out
                      << "\"" << std::endl;

            PAUSE_ENTER();
        }
    }

    void test_packet()
    {
        for(int i = 0; i < 3; ++i)
        {
            ///-------------------------------|
            /// Create a socket for           |
            /// communicating with the server.|
            ///-------------------------------:
            sf::TcpSocket socket;

            if (socket.connect(address_server, port) != sf::Socket::Done)
                return;

            std::cout << "Connect to the server "
                      << address_server;

            info(" GOOD\n", 10);

            ///-------------------------------|
            /// Receive a message             |
            /// from the server.              |
            ///-------------------------------:
            sf::Packet packet;
            if (socket.receive(packet) != sf::Socket::Done)
            {   info_err(L"sf::Socket::Done is FALSE");
                return;
            }
            else
            {   Data data; packet >> data; info_in(data);
            }

            ///-------------------------------|
            /// Send an answer to the server. |
            ///-------------------------------:
            sf::Packet      packet_out;
                            packet_out << data_out;
            if (socket.send(packet_out) != sf::Socket::Done)
            {   info_err(L"sf::Socket::Done is FALSE");
                return;
            }
            else info_out(data_out);

          //PAUSE_ENTER();

            data_out.mess = input_str();
        }
    }

private:
    ///-------------------------------|
    /// Ask for the server address.   |
    ///-------------------------------:
    bool set_address(sf::IpAddress& addr) const
    {
        addr = cfg::ADDRESS_SERVER;

        if (addr == sf::IpAddress::None)
        {   std::cout << "ERROR: Address server "
                      << addr
                      << " not corrected\n";
            return false;
        }   return true ;
    }
};

inline void testclass_Client(const Account& acc)
{   std::system("mode 60, 30");
    std::cout << __FUNCTION__ << '\n';

    win::set_window_name((std::string("Client") + acc.to_string()).c_str());

    Client client(acc);

    std::cout << "Client FINISHED\n";
    std::cin.get();
}

#endif // CLIENT_H

