#ifndef CONFIG_H
#define CONFIG_H

///----------------------------------------------------------------------------|
/// "_config.h"
///----------------------------------------------------------------------------:
#include <string_view>
#include <iostream>
#include <vector>
#include <list>
#include <map>

namespace cfg
{

enum eTRANSPORT_MODE
{   TRANSPORT_STRING,
    TRANSPORT_PACKET
};

eTRANSPORT_MODE TRANSPORT_MODE = TRANSPORT_PACKET;

const unsigned short  PORT =  50001     ;
const char* ADDRESS_SERVER = "127.0.0.1";

const short ATRB_DEFAULT   = 7;

struct  Config
{   Config()
    {
    }

    void foo()
    {
    }
};

} /// namespace cfg

inline void testclass_Config()
{   std::cout << __FUNCTION__ << '\n';



    std::cin.get();
}

#define l(v)       std::cout << #v << " = " << (v) << "\n";
#define ll         std::cin.get();
#define PRESSENTER std::cin.get()

struct  Plot
{   int x, y;

    Plot operator+ (const Plot& p) const { return {x +  p.x ,  y +  p.y}; }
    bool operator==(const Plot& p) const { return  x == p.x && y == p.y ; }
    bool operator!=(const Plot& p) const { return  x != p.x || y != p.y ; }
};

namespace win
{
#include <windows.h>

void set_window_name(std::string_view name)
{   SetConsoleTitle (name.data());
}

void  sleep  (int ms)
{   Sleep(ms);
}

short convert(short text, short background)
{   return   (background  << 4) | text;
};

///---------------------|
/// Экран.              |
///---------------------:
struct  Screen
{   Screen(Plot st) : start({(short)st.x, (short)st.y})
    {   h = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleCursorInfo   (h, &cci);
        SetConsoleTextAttribute(h,    4);
    }

    HANDLE              h;
    CONSOLE_CURSOR_INFO cci = { sizeof(cci), false };
    COORD start;

    void to(const Plot p, char sign, WORD color) const
    {   COORD c = {(SHORT)((int)start.X + p.x), (SHORT)((int)start.Y + p.y)};
        SetConsoleCursorPosition(h, c    );
        SetConsoleTextAttribute (h, color);
        putchar(sign);
    }

    void to(const Plot p, char sign) const
    {   COORD c = {(SHORT)((int)start.X + p.x), (SHORT)((int)start.Y + p.y)};
        SetConsoleCursorPosition(h, c    );
        putchar(sign);
    }

    void setatr(short a) const
    {   SetConsoleTextAttribute (h, a);
    }

    void carret_visible(bool visible = false) const
    {   CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = visible;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }

    void set_cursor(const Plot p) const
    {   SetConsoleCursorPosition(h, { short(p.x), short(p.y) });
    }

    void set_cursor(const Plot p, short text, short background) const
    {   SetConsoleCursorPosition(h, { short(p.x), short(p.y)});
        SetConsoleTextAttribute (h, (background  << 4) | text);
    }

    void set_cursor(const Plot p, short atrb) const
    {   SetConsoleCursorPosition(h, { short(p.x), short(p.y)});
        SetConsoleTextAttribute (h, atrb);
    }

    static std::string color_str(std::string_view str, short atrb)
    {   HANDLE _h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(_h, atrb);
        std::cout << str;
        SetConsoleTextAttribute(_h, cfg::ATRB_DEFAULT);
        return "";
    }

    static std::wstring color(short atrb = cfg::ATRB_DEFAULT)
    {   HANDLE _h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(_h, atrb);
        return L"";
    }
};

} /// namespace win

#endif // CONFIG_H

