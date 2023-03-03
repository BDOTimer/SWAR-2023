#ifndef MESS_H
#define MESS_H
///----------------------------------------------------------------------------|
/// "_mess.h"
///----------------------------------------------------------------------------:

#include "_config.h"

struct  Mess
{
    std::string whom   ;
    const short ATRBin ;
    const short ATRBerr;
    const short ATRBout;

        Mess(const char* Whom) :
                whom    (Whom),
                ATRBin (win::convert(11, 0)),
                ATRBerr(win::convert(12, 0)),
                ATRBout(win::convert( 5, 0))
        {
        }

    void info_in (const Data& data) const
    {
        if(is_silent()) return;

        std::wcout  << "Answer received from " << whom.c_str() << ':';

        {   win::Color paint(ATRBin); std::wcout << data;
        }
    }

    void info_out(const Data& data) const
    {   if(is_silent()) return;

        std::wcout  << "Message sent to "      << whom.c_str() << ':';

        {   win::Color paint(ATRBout); std::wcout << data;
        }
    }

    void info_err(std::wstring_view str) const
    {   if(is_silent()) return;

        {   win::Color paint(ATRBerr); std::wcout << str;
        }
    }

    void info(std::string_view str, short atrb) const
    {   if(is_silent()) return;

        std::cout << win::Screen::color_str(str, atrb);
    }

private:
    bool is_silent() const
    {   return cfg::isSERVER_SILENT && whom == "client";
    }
};

#endif // MESS_H
