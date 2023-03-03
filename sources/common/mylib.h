#ifndef MYLIB_H
#define MYLIB_H

#include <thread>
#include <chrono>

///----------------------------------------------------------------------------|
/// "mylib.h"
///----------------------------------------------------------------------------:
namespace myl{

struct  Plot
{   int x, y;

    Plot operator+ (const Plot& p) const { return {x +  p.x ,  y +  p.y}; }
    bool operator==(const Plot& p) const { return  x == p.x && y == p.y ; }
    bool operator!=(const Plot& p) const { return  x != p.x || y != p.y ; }
};


void sleep(int ms)
{   std::this_thread::sleep_for(std::chrono::milliseconds {ms});
}

void PAUSETIME(int seconds)
{
    for(int i = seconds; i >= 0; --i)
    {
        std::string s = std::to_string(i);

        int n = 3 - s.size();

        for(int j = 0; j < n; ++j)
        {   s.push_back(' ');
        }

        std::cout << "\b\b\b" << s;

        sleep(1000);
    }
}

} // namespace myl

#endif // MYLIB_H
