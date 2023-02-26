#ifndef HEADER_9AABE788BCA9A156
#define HEADER_9AABE788BCA9A156

///----------------------------------------------------------------------------|
/// "_client.h"
///----------------------------------------------------------------------------:
#ifndef CLIENT_H
#define CLIENT_H

#include "_mysfml.h"


struct  Client
{   Client(Account acc) :  ATRBin (win::convert(11, 0)),
                           ATRBout(win::convert(12, 0)),
                           account(acc)
    {
        set_address(address_server);

                  data_out = {account, 2023, L"Привет, Мир!"};
        packet << data_out;

        switch ( cfg::TRANSPORT_MODE )
        {   case cfg::TRANSPORT_STRING: test_01();
            case cfg::TRANSPORT_PACKET: test_02();
        }
    }

    unsigned short port = cfg::PORT;
    sf::IpAddress  address_server  ;

    const short   ATRBin ;
    const short   ATRBout;
    const Account account;

    Data         data_out;
    sf::Packet     packet;

    void test_01()
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
                      << win::Screen::color_str(" GOOD\n", 10);

            ///-------------------------------|
            /// Receive a message             |
            /// from the server.              |
            ///-------------------------------:
            char in[128];
            std::size_t received;
            if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
                return;
            std::cout << "Message received from the server: \""
                      << win::Screen::color_str(in, ATRBin)
                      << "\"" << std::endl;

            ///-------------------------------|
            /// Send an answer to the server. |
            ///-------------------------------:
            const char out[] = "Hi, I'm a client ";
            std::string Out(out);
                        Out += account.to_string();

            if (socket.send(Out.c_str(), Out.size()) != sf::Socket::Done)
                return;
            std::cout << "Message sent to the server: \""
                      << win::Screen::color_str(Out, ATRBout)
                      << "\"" << std::endl;

            PRESSENTER;
        }
    }

    void test_02()
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
                      << win::Screen::color_str(" GOOD\n", 10);

            ///-------------------------------|
            /// Receive a message             |
            /// from the server.              |
            ///-------------------------------:
            char in[128];
            std::size_t received;
            if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
                return;
            std::cout << "Message received from the server: \""
                      << win::Screen::color_str(in, ATRBin)
                      << "\"" << std::endl;

            ///-------------------------------|
            /// Send an answer to the server. |
            ///-------------------------------:
            if (socket.send(packet) != sf::Socket::Done) return;
            std::wcout << "Message sent to the server: \""
                       << win::Screen::color(ATRBout) << data_out
                       << win::Screen::color()
                       << "\"" << std::endl;

            PRESSENTER;
        }
    }

private:
    ///-------------------------------|
    /// Ask for the server address.   |
    ///-------------------------------:
    void set_address(sf::IpAddress& addr) const
    {
        addr = cfg::ADDRESS_SERVER;

        if (addr == sf::IpAddress::None)
        {   std::cout << "ERROR: Address server "
                       << addr
                       << " not corrected\n";
        }
    }
};

inline void testclass_Client(const Account& acc)
{   std::cout << __FUNCTION__ << '\n';
    win::set_window_name((std::string("Client") + acc.to_string()).c_str());

    Client client(acc);

    std::cout << "Client FINISHED\n";
    std::cin.get();
}

#endif // CLIENT_H
#endif // header guard

