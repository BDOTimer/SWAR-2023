#include "game.h"

///------------------------------------|
/// Все тесты тут.                     |
///------------------------------------:
inline void testall()
{
  //testfoo_rrand                 ();
  //testclass_FieldRanking        ();
  //testclass_FieldRanking_1000   ();
  //testclass_FieldRanking_Present();

  //testclass_Flotilia     ();
  //testclass_FlotGenerator();

  //testclass_World();
    testclass_Game ();
}

#include "windows.h"

///----------------------------------------------------------------------------|
/// Старт.
///----------------------------------------------------------------------------:
int main()
{ //srand((unsigned)time(0));
    srand    (1003 );
    setlocale(0, "");
    SetConsoleTitleW(L"Морской Бой - 2022");

    myl::BANNER(
    L"///-----------------------------------|" ,
    L"///        Морской Бой -2022!         |" ,
    L"///-----------------------------------:");

    try
    {   testall();
    }
    catch(std::string& err){ std::cout << err    << '\n'; }
    catch(...)             { std::cout << "ERROR: ???\n"; }

    myl::BANNER(
    "///-----------------------------------|" ,
    "///        Programm FINISHED!         |" ,
    "///-----------------------------------.");

    std::cin.get();
}
