#ifndef HEADER_A67155DDA055E12F
#define HEADER_A67155DDA055E12F

///----------------------------------------------------------------------------|
/// "command.h"
///----------------------------------------------------------------------------:
#ifndef COMMAND_H
#define COMMAND_H

#include "_config.h"

///----------------------------------------------------------------------------|
/// Account.
///----------------------------------------------------------------------------:
struct Account
{
    std::string nick    ;
    std::string password;

    const auto to_string() const
    {   return std::string(" account:{") +
               nick + ", " + password + "}";
    }
};

inline std::ostream& operator <<(std::ostream& o, const Account& acc)
{	return o << acc.to_string();
}

inline sf::Packet& operator    <<(sf::Packet& packet, const Account& acc)
{	return packet  << acc.nick << acc.password;
}

inline sf::Packet& operator    >>(sf::Packet& packet, Account&  acc)
{	return packet  >> acc.nick >> acc.password;
}

///----------------------------------------------------------------------------|
/// Пакет.
///----------------------------------------------------------------------------:
struct Data
{	Account       acc;

    int            id; /// Идентификатор игрока.
	std::wstring mess; /// Сообщение.

	enum eCOMMAND
	{    E_EMPTY = 0,
	     E_READY    ,
	     E_WAIT     ,
	     E_LET      ,
	     E_FINISH   ,
	     E_MESSAGE  ,
	     E_SPEC
	} COMMAND;          /// Команда.
};

std::map<Data::eCOMMAND, std::wstring> voc =
{	{   Data::E_EMPTY  , L"EMPTY"                  },
    {   Data::E_READY  , L"Авторизация успешна!"   },
	{   Data::E_WAIT   , L"Жди ход противника ... "},
	{   Data::E_LET    , L"Давай! Твой ход!"       },
	{   Data::E_FINISH , L"Игра закончена ..."     },
	{   Data::E_MESSAGE, L"Прими сообщение!"       },
	{   Data::E_SPEC   , L"COMMAND"                }
};

inline std::wostream& operator <<(std::wostream& packet, const Data& data)
{	       std::cout  << data.acc.to_string();
    return std::wcout << int(data.id)  << L", "
	                  << data.mess     << L", "
	                  << voc[data.COMMAND]    ;
}

inline sf::Packet& operator  <<(sf::Packet& packet, const Data&  data)
{	return packet << data.acc << data.id << data.mess
                  << (sf::Uint32)data.COMMAND;
}

inline sf::Packet& operator  >>(sf::Packet& packet, Data&  data)
{	sf::Uint32 n;
	packet >> data.acc >> data.id >> data.mess >> n;
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

struct  Command
{       Command()
        {
        }

    void foo()
    {

    }
};


inline void testclass_Command()
{   std::cout << __FUNCTION__ << '\n';



    std::cout << "Command FINISHED\n";
}

#endif // COMMAND_H
#endif // header guard

