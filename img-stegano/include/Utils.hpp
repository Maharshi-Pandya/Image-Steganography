// Utils file for bin, int, str conversions
#pragma once
#if !defined(_UTILS_)
#define _UTILS_

#define bitsize 8   // 8 bits = 1 byte u stupid

// includes
#include <iostream>
#include <bitset> // may be needed idk

namespace utils
{
  // char(int) to bin (bitset)
  std::bitset<bitsize> toBinStr(uint decNum)
  {
    std::bitset<bitsize> binNumSet(decNum);
    return binNumSet;   // eassyyy 
  }
}

#endif // _UTILS_