#ifndef CONFIG_H
#define CONFIG_H

#include "mylib.h"

///------------------------------------|
/// Правило на состав флотилии.        |
/// Размер -> кол-во лодок.            |
/// Число  -> кол-во палуб в лодке.    |
///------------------------------------:
struct  Cfg
{       Cfg()
        {
            ///------------------------------|
            /// Сначала с большим кол. палуб.|
            ///------------------------------:
            if(!std::is_sorted(std::begin(rule), std::end(rule)))
            {   std::   sort  (std::begin(rule), std::end(rule),
                               std::greater<int>());
            }
        };

    size_t C = 12,
           R = 12;

    std::vector<size_t> rule = {5, 4,4, 3,3,3, 2,2,2,2, 1,1,1,1,1};
  //std::vector<size_t> rule = {5, 4,4,4, 1,1};
};

inline Cfg cfg;

#endif // CONFIG_H
