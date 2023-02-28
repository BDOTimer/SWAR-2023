#ifndef MYLIB_H
#define MYLIB_H

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <tuple>
#include <list>

#define ASSERT(u) if(!(u))  \
                  std::cout << myl::to_string("ASSERT: -> line: ", __LINE__)\
                            << '\n'
#define ERROR_(v)  myl::to_string("ERROR: ", v, " -> line: ", __LINE__)
#define l(v)      std::cout << #v << " = " << v << "\n";

namespace std
{
    std::string to_string(const char*       s) { return s; }
    std::string to_string(const std::string s) { return s; }
}

#include <ctime>
#include <cstdlib>
///---------|
/// my lib  |
///---------:
namespace myl
{
    template <typename... TT>
    std::string to_string(TT&& ... a)
    {   return (std::to_string(a) + ...) + "\n";
    }

    template <typename ... TT>
    void BANNER(TT&&   ... a )
    {   ((std::wcout   <<  a << std::endl), ...);
    }

    static int rrand(int range_min, int range_max)
    {   return rand() % (range_max - range_min) + range_min;
    }

    template <typename T>
    void info(const T& m)
    {   for(const auto&  row : m)
        {   std::cout << row << '\n';
        }   std::cout        << '\n';
    }
}

inline void testfoo_rrand()
{
    for(int    i = 0; i < 100; ++i)
    {   auto   r = myl::rrand(0, 5);
        auto   b = 0 <= r && r < 5;
        ASSERT(b);
        if   (!b) return;
    }
    std::cout << __FUNCTION__ << " success!\n";
}

struct Point2i
{   size_t x, y;

    bool operator==(const Point2i& p) const { return p.x == x && p.y == y; }

    void debug() const
    {   std::cout << "{" << x << ", " << y << "}\n";
    }
};

#endif // MYLIB_H
