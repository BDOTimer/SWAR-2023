///----------------------------------------------------------------------------|
/// "main.cpp"
///----------------------------------------------------------------------------:
#include "_runner.h"

int tests()
{   testclass_Config();

    std::cout << "FINISH TESTS\n";
    return  0;
}


int main(const int n, const char** arg)
{
  //setlocale(0, "");
    setlocale(LC_ALL, "Russian");
    system   ("chcp 1251 > nul");

  //return tests  ();

    cfg::Config load;

    std::wcout << L"Запуск ...    "; //myl::PAUSETIME(5);
    std::wcout << L"\n";

    if(n > 1)
    {
        if     (         std::string("server") == arg[1])
        {   testclass_Server();
        }
        else if(n > 3 && std::string("client") == arg[1])
        {   testclass_Client({arg[2], arg[3]});
        }
    }
    else testclass_Runner();
}
