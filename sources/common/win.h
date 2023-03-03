#ifndef WIN_H
#define WIN_H
///----------------------------------------------------------------------------|
/// "win.h"
///----------------------------------------------------------------------------:

#ifdef    __WIN32__
    #define WINDOWSCOLOR
#endif // __WIN32__

#include <string_view>
#include "mylib.h"

#ifdef WINDOWSCOLOR

namespace win
{
#include <windows.h>

const short ATRB_DEFAULT = 7;

using myl::Plot;

void set_window_name(std::string_view name)
{   SetConsoleTitle (name.data());
}

constexpr short convert(short text, short background)
{   return                    text  |    (background << 4);
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
        SetConsoleTextAttribute(_h, ATRB_DEFAULT);
        return "";
    }

    static std::wstring color(short atrb = ATRB_DEFAULT)
    {   HANDLE _h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(_h, atrb);
        return L"";
    }
};

struct  Color
{       Color(short col){ Screen::color(col); }
       ~Color(         ){ Screen::color(   ); }
};

void PAUSE_ENTER()
{   Screen::color_str("PRESS ENTER!\n", 14);
    std::cin.get();
}

void SetConsoleRus()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

} /// namespace win

#else

typedef short WORD;

namespace win
{

const short ATRB_DEFAULT = 7;

using myl::Plot;

void set_window_name(std::string_view name)
{   //SetConsoleTitle (name.data());
}

constexpr short convert(short text, short background)
{   return                    text  |    (background << 4);
};

///---------------------|
/// Экран.              |
///---------------------:
struct  Screen
{       Screen(Plot st) : start(st)
        {
        }

    Plot start;

    void to(const Plot p, char sign, WORD color) const
    {   /// this linux ...
    }

    void to(const Plot p, char sign) const
    {   /// this linux ...
    }

    void setatr(short a) const
    {   /// this linux ...
    }

    void carret_visible(bool visible = false) const
    {   /// this linux ...
    }

    void set_cursor(const Plot p) const
    {   /// this linux ...
    }

    void set_cursor(const Plot p, short text, short background) const
    {   /// this linux ...
    }

    void set_cursor(const Plot p, short atrb) const
    {   /// this linux ...
    }

    static std::string color_str(std::string_view str, short atrb)
    {   /// this linux ...
        std::cout << str;
        return "";
    }

    static std::wstring color(short atrb = ATRB_DEFAULT)
    {   /// this linux ...
        return L"";
    }
};

void PAUSE_ENTER()
{   std::cout << "PRESS ENTER!\n";
    std::cin.get();
}

struct  Color
{       Color(short col){  }
       ~Color(         ){  }
};

void SetConsoleRus()
{
}

} /// namespace win
#endif

#endif // WIN_H

