#ifndef COMMAND_H
#define COMMAND_H

///----------------------------------------------------------------------------|
/// "command.h"
///----------------------------------------------------------------------------:

#include "_config.h"

///----------------------------------------------------------------------------|
/// Account.
///----------------------------------------------------------------------------:
struct Account
{
    std::string nick    ;
    std::string password;

    const auto to_string() const
    {   return !nick.empty() && !nick.empty() ?
                std::string("account:[") +
                nick + ", " + password   + "]" : "";
    }
};

inline std::ostream& operator <<(std::ostream& o, const Account& acc)
{	return o  << acc.to_string();
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

    int            id; /// Идентификатор игрока на сервере.
	std::wstring mess; /// Сообщение.

	enum eCOMMAND
	{    E_EMPTY = 0,
	     E_READY    ,
	     E_WAIT     ,
	     E_LET      ,
	     E_FINISH   ,
	     E_MESSAGE  ,
	     E_SPEC     ,
	     /// ...
	     E_end

	} COMMAND;         /// Команда.

	static const wchar_t* voc[];
};

///---------------------------|
/// Расшифровка команд.       |
///---------------------------:
const wchar_t* Data::voc[] =
{
    L"EMPTY(command)"         ,
    L"Авторизация успешна!"   ,
	L"Жди ход противника ... ",
	L"Давай! Твой ход!"       ,
	L"Игра закончена ..."     ,
	L"Прими сообщение!"       ,
	L"COMMAND"
};

inline std::wostream& operator <<(std::wostream& packet, const Data& data)
{	       std::cout  << "\n{"
                      <<  "\n    " << data.acc.to_string  ();
    return std::wcout << L"\n    " << int(data.id)
	                  << L"\n    " << data.mess
	                  << L"\n    " << data.voc[data.COMMAND]
	                  << L"\n}"    << std::endl;
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

	std::wstring       s ;
	getline(std::wcin, s);
	return             s ;
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

