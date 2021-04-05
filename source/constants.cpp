#include "constants.hpp"

const char * add(const char* __str1, const char* __str2)
{
    static std::string str1(__str1);
    str1 = str1 + __str2;
    return str1.c_str();
}