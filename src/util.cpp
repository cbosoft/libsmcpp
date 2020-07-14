#include "util.hpp"


std::string type_to_str(uint32_t type)
{
    std::string s;
    int shift = 24;
    for (int i = 0; i < 4; i++)
    {
        s += (type >> shift) & 0xff;
        shift -= 8;
    }
    return s;
}