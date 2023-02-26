#ifndef RUNNER_H
#define RUNNER_H
///----------------------------------------------------------------------------|
/// "_runner.h"
///----------------------------------------------------------------------------:


#include "_server.h"
#include "_client.h"

struct  Runner
{       Runner  ()
        {   loop();
        }

private:

    void loop()
    {
        std::wcout << L"Для запуска сервера PRESS ENTER\n"; std::cin.get();
        std::system("start main server");


        while(true)
        {
            if(0 == cnt_id) std::wcout << L"Для запуска клиента PRESS ENTER";
            else            std::wcout << L"...     ещё клиент  PRESS ENTER";

            std::cin.get(); std::wcout << L"... запуск!\n";

            Account acc = generate_acc();
            std::system(generate_command_arg(acc).c_str());
        }
    }

    size_t cnt_id = 0;

    Account generate_acc()
    {
        Account   acc;
                  acc.nick     = "nick-";
                  acc.nick    +=  std::to_string(++cnt_id);
                  acc.password = "*password*";
        return    acc;
    }

    std::string generate_command_arg(const Account& acc) const
    {   return  std::string("start main client ") + acc.nick    + " "
                                                  + acc.password;
    }
};

inline void testclass_Runner()
{   std::system("mode 40,30");
    std::cout << __FUNCTION__ << '\n';
    win::set_window_name("RUNNER - 2023");

    Runner runner;

    std::cout << "Runner FINISHED\n";
}

#endif // RUNNER_H


