///----------------------------------------------------------------------------|
/// Tcp Sokets.
///----------------------------------------------------------------------------:
#define   SFML_STATIC
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#define  l(v)  std::cout << #v << " = " << v << "\n";

///----------------------------------------------------------------------------|
/// Пакет.
///----------------------------------------------------------------------------:
struct Data
{	sf::Uint8   number; /// Номер игрока.
	std::wstring   mess; /// Сообщение.

	enum eCOMMAND
	{    E_READY = 0,
	     E_WAIT     ,
	     E_LET      ,
	     E_FINISH   ,
	     E_MESSAGE
	} COMMAND;          /// Команда.
};

std::map<Data::eCOMMAND, std::wstring> voc =
{	{   Data::E_READY   , L"Авторизация успешна!"   },
	{   Data::E_WAIT    , L"Жди ход противника ... "},
	{   Data::E_LET     , L"Давай! Твой ход!"       },
	{   Data::E_FINISH  , L"Игра закончена ..."     },
	{   Data::E_MESSAGE , L"Прими сообщение!"       }
};

inline std::wostream& operator <<(std::wostream& packet, const Data& data)
{	return std::wcout << int(data.number)  << L", "
	                  << data.mess         << L", "
	                  << voc[data.COMMAND]      ;
}

inline sf::Packet& operator <<(sf::Packet& packet, const Data& data)
{	return packet << data.number << data.mess << (sf::Uint32)data.COMMAND;
}

inline sf::Packet& operator >>(sf::Packet& packet, Data& data)
{	sf::Uint32 n;
	packet >> data.number >> data.mess >> n;
	data.COMMAND = (Data::eCOMMAND)n;
	return packet;
}

inline std::wstring user_input( )
{	//std::cin.clear();
	//std::cin.sync ();

	while(std::wcin.peek() == L'\n') std::wcin.ignore(1, L'\n');

	std::wstring      s ;
	getline(std::wcin, s);
	return            s ;
}

inline void pause()
{	while(std::wcin.peek() == L'\n') std::wcin.get();
	std::cin.get();
}

void log_(const char* f, int l, const wchar_t* m)
{	std::wcout <<  "\nERROR      : " << m
               <<  "\n       FILE: " << f 
               <<  "\n       LINE: " << l << "\n\n";
}
void log_(const char* f, int l, const char* m)
{	std::cout  <<  "\nERROR      : " << m
               <<  "\n       FILE: " << f 
               <<  "\n       LINE: " << l << "\n\n";
}
#define LOG_ERROR(a) log_(__FILE__, __LINE__, a)
#define sig          { static int cnt = 0; l(cnt++) std::wcin.get();}

///----------------------------------------------------------------------------|
/// Common.
///----------------------------------------------------------------------------:
struct Common
{	static const char* info_status(std::string               s     , 
                                   const sf::Socket::Status& status)
	{	
		s +=  " status != sf::Socket::Done -> ";
		switch(status)
		{	case sf::Socket::NotReady:
			{	return (s + "NotReady").c_str();
			}
			case sf::Socket::Partial:
			{	return (s + "Partial" ).c_str();
			}
			case sf::Socket::Error:
			{	return (s + "Error"   ).c_str();
			}
			default:
				return (s + "... ???" ).c_str();
		}
	}
};

///----------------------------------------------------------------------------|
/// TCPServer.
///----------------------------------------------------------------------------:
struct  TCPServer : public Common
{		TCPServer(unsigned short port) : psocket(nullptr)
	{	//sf::IpAddress ip_server = "127.0.0.1";//"192.168.0.5";
		run(port);
	}
	~TCPServer()
	{	cargo_clear();
	}

private:

	Data data_in ;
	Data data_out;

	sf::TcpListener listener;
	sf::TcpSocket*  psocket ;
	int run(unsigned short port) ///----------------------------------------run:
	{	
	
		int error = 0;
		///---------------------|
		/// Слушатель.          |
		///---------------------:
		listener.setBlocking(false);
		sf::Socket::Status
		    status  = listener.listen(port);
		if (status != sf::Socket::Done)
		{	/// NotReady, Partial, Disconnected, Error
			LOG_ERROR(info_status("Server: run:", status));
			pause    ( );
			return   111;
		}

		std::cout << "Server is listening to port "
		          << port
		          << ", waiting for connections... " << std::endl;

		while  (error == 0)
		{	    error = connected();
		
			for(auto socket : cargo)
			{	error = receiver(*socket);
			}
		}
		return error;
	}

	int connected() ///-----------------------------------------------connected:
	{	///---------------------|
		/// Ловись, ... !       |
		///---------------------:
		if(psocket == nullptr)    psocket = new sf::TcpSocket;
		sf::TcpSocket&  socket = *psocket;

		sf::Socket::Status
		status  = listener.accept(socket);
		if (status == sf::Socket::Done)
		{	///---------------------|
			/// Поймлась рыбка.     |
			///---------------------:
			std::cout << "Client connected: "
			          << socket.getRemoteAddress() << std::endl;

			///---------------------|
			/// Рыбку в садок.      |
			///---------------------:
			cargo .push_back  (psocket);
			socket.setBlocking(false  );

			///---------------------|
			/// Готовим ответ ...   |
			///---------------------:
			data_out.number  =    1                      ;
			data_out.mess    =  L"Hi, I'm the server ...";
			data_out.COMMAND =    Data::E_READY          ;

			sf::Packet  pack;
			pack << data_out;

			if (socket.send(pack) == sf::Socket::Done)
			{	std::wcout << L"Message sent to the client: \n    \""
				           <<  data_out
				           << L"\"" << std::endl;

				///------------------------|
				/// Готовим место для      |
				/// следующего соединения. |
				///------------------------:
				psocket =  nullptr ;
			}
			else
			{	/// NotReady, Partial, Disconnected, Error
				LOG_ERROR(info_status("Server: connected:", sf::Socket::Error));
				pause      (      );
				return        121  ;
			}

		}
		else if (status == sf::Socket::Error)
		{	LOG_ERROR(info_status("Server: connected:", status));
			pause  ( );
			return 122;
		}
		return 0;
	}

	int receiver(sf::TcpSocket& socket) ///---------------------------receiver:
	{	///---------------------|
		/// Чё, скажешь?        |
		///---------------------:
		sf::Packet pack;
		sf::Socket::Status status = socket.receive(pack);
		if(status == sf::Socket::NotReady)
		{	/// ...
		}
		else if (status != sf::Socket::Done)
		{	/// NotReady, Partial, Disconnected, Error
			LOG_ERROR(info_status("Server: receiver:", status));
			pause  ( );
			return 131;
		}
		else if(status == sf::Socket::Done)
		{	std::wstring  s;
			pack       >> s;

			std::wcout << L"From client: \""
			           << s << "\"" << std::endl;

			///---------------------|
			/// Ok.                 |
			///---------------------:
			sf::Packet pack;
			           pack << std::wstring(L"Ok.");

			    status  = socket.send(pack);
			if (status != sf::Socket::Done)
			{	/// NotReady, Partial, Disconnected, Error
				LOG_ERROR(info_status("Server: receiver:", status));
				pause  ( );
				return 132;
			}
		}
		return 0;
	}

	std::vector<sf::TcpSocket*> cargo;

	void cargo_clear()
	{	for(auto& e : cargo) delete e;
		cargo.clear ();
	}
};

///----------------------------------------------------------------------------|
/// TCPClient.
///----------------------------------------------------------------------------:
struct  TCPClient : public Common
{		TCPClient(unsigned short port)
		{	run(port);
		}

private:
	Data data_in ;
	Data data_out;

	sf::TcpSocket socket;
	int run(unsigned short port) ///---------------------------------Client::run
	{	sf::IpAddress adr_server = "127.0.0.1";

		std::cout << "Address or name of the server to connect to: "
		          << adr_server << "\n";
		if (adr_server == sf::IpAddress::None)
		{	LOG_ERROR(info_status("Client: Fail syntax net Address:", 
										   			   	    sf::Socket::Error));
			pause  ( );
			return 211;
		}

		///---------------------|
		/// Ау?!                |
		///---------------------:
		sf::Socket::Status status = socket.connect(adr_server, port);

		if (status != sf::Socket::Done)
		{	LOG_ERROR(info_status("Client: run:", status));
			pause  ( );
			return 212;
		}

		std::cout << "Connected to server "
		          << adr_server << std::endl;

		///---------------------|
		/// Ага.                |
		///---------------------:
		sf::Packet pack;
		if (socket.receive(pack) != sf::Socket::Done)
		{	LOG_ERROR(info_status("Client: run:", sf::Socket::Error));
			return 213;
		}

		pack       >> data_in;
		std::wcout << L"Message received from the server: \n    \""
		           << data_in << L"\"" << std::endl;

		///---------------------|
		/// Снимаем блокировку. |
		///---------------------:
		socket.setBlocking(false);

		///---------------------|
		/// Гипер-Лупер.        |
		///---------------------:
		int   error  = 0;
		while(error == 0 || error == 777)
		{	error = sender  ();

			while(error != 777)
				error = receiver();
		}

		return 0;
	}

	int receiver() ///------------------------------------------Client::receiver
	{	///---------------------|
		/// Слушаю.             |
		///---------------------:
		sf::Packet packin;
		sf::Socket::Status status = socket.receive(packin);
		if(status == sf::Socket::Done)
		{	std::wstring  in;
			packin     >> in;
			std::wcout << L"From server: \""
			           << in << L"\"" << std::endl;
			return 777;
		}
		else if(status == sf::Socket::NotReady)
		{	/// ...
		}
		else if (status != sf::Socket::Done)
		{	/// NotReady, Partial, Disconnected, Error
			LOG_ERROR(info_status("Client: receiver:", status));
			pause  ( );
			return 221;
		}
	}

	int sender() ///----------------------------------------------Client::sender
	{	///---------------------|
		/// Говорю.             |
		///---------------------:
		std::wstring s = user_input(); ///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<!
		sf::Packet  packout          ;
		packout  << s                ;

		sf::Socket::Status status  = socket.send(packout);
		if (status != sf::Socket::Done)
		{	/// NotReady, Partial, Disconnected, Error
			LOG_ERROR(info_status("Client: sender:", status));
			pause  ( );
			return 231;
		}
	}
};

