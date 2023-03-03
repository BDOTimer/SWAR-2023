#ifndef DEBUG_H
#define DEBUG_H
///----------------------------------------------------------------------------|
/// "debug.h"
///----------------------------------------------------------------------------:
#define MYDEBUG

#ifdef MYDEBUG
#define ASSERT(U) if(!(U)) std::cout << "\aASSERT: file:" \
                                         << __FILE__          \
                                         << ", line:"         \
                                         << __LINE__  << '\n' ;
#define l(v)      std::cout << #v << " = " << (v) << '\n' ;
#define ll        std::cin.get();
#else
#define ASSERT(U)
#define l(v)
#define ll
#endif

struct  CustomException : public std::exception
{       CustomException(int line, const char* filename)
        {   reason = std::string("ERROR_EXCEPTION: File: "  ) +
                                               sub(filename ) +
                            ", Line: " + std::to_string(line) ;
        }

    std::string LEFT = "sources";
    std::string reason;

    virtual const char* what() const throw()
    {   return  reason.c_str();
    }

    std::string sub(std::string s)
    {   const auto pos = s.find  (LEFT) + LEFT.size() + 1;
        return           s.substr(pos, s.size() - pos);
    }
};


#define ERROR_EXCEPTION CustomException(__LINE__, __FILE__)

#endif // DEBUG_H
