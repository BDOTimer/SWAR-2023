#ifndef CONFIG_H
#define CONFIG_H

///----------------------------------------------------------------------------|
/// "_config.h"
///----------------------------------------------------------------------------:
#include <string_view>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>

#include "debug.h"
#include "../common/mylib.h"
#include "../common/win.h"

namespace cfg
{

bool isSERVER_SILENT = true;

enum eTRANSPORT_MODE
{   TRANSPORT_STRING,
    TRANSPORT_PACKET
};

eTRANSPORT_MODE TRANSPORT_MODE = TRANSPORT_PACKET;

unsigned short        PORT =  50002     ;
std::string ADDRESS_SERVER = "127.0.0.1";

struct  Config
{       Config  ()
        {   load();
          //info();
            init();
        }

    void load()
    {
        int cnt = 0;
        std::ifstream config("config.txt");
        if(config.is_open())
        {   std::wcout << L"ЗАГРУЗКА ДАННЫХ ИЗ КОНФИГ-ФАЙЛА... ";

            while(config)
            {
                std::string name ; config >> name;
                std::string value; config >> value;

                if(!name.empty() && !value.empty())
                {   m[name] = value; ++cnt;
                }
                else break;
            }
            std::wcout << L"всего: " << cnt << '\n';
        }
    }

private:
    std::map<std::string, std::string> m;

    void info()
    {   for(const auto&[name, value] : m)
        {   std::cout << name << " = " << value << '\n';
        }
    }

    void init()
    {   try
        {
            std::string      port   = m["PORT"  ];
            std::string_view adress = m["ADRESS"];
            PORT  = std::stoi(port);
            ADDRESS_SERVER = adress;

            std::cout << "PORT           = " << PORT           << '\n';
            std::cout << "ADDRESS_SERVER = " << ADDRESS_SERVER << '\n';
        }
        catch(...)
        {   std::cout << "catch ERROR: Read config file\n";
        }
    }
};

} /// namespace cfg

inline void testclass_Config()
{   std::cout << __FUNCTION__ << '\n';

    cfg::Config load;

    std::cin.get();
}

inline void PAUSE_ENTER()
{
    win::PAUSE_ENTER();
}

inline std::wstring input_str(std::wstring_view promt = L"INPUT MESSAGE: ")
{
    {
        win::Color paint(14);
        std::wcout <<  promt;
    }

    std::wstring s; std::getline(std::wcin, s);
    return       s;
}

#endif // CONFIG_H

