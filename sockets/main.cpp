///----------------------------------------------------------------------------|
/// "main.cpp"
///----------------------------------------------------------------------------:

#include "_runner.h"


int main(const int n, const char** arg)
{
    setlocale(0, "");

    std::wcout << L"Запуск ...\n";

    if(n > 1)
    {
        if(std::string("server") == arg[1])
        {
            testclass_Server();
        }
        else if(n > 3 && std::string("client") == arg[1])
        {
            testclass_Client({arg[2], arg[3]});
        }
    }
    else testclass_Runner();
}
