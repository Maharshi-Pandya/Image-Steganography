// Utils file for bin, int, str conversions
#pragma once
#if !defined(_UTILS_)
#define _UTILS_

#define bitsize 8   // enough

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
  // get the byte from the binary string
  uint byteFromBinStr(std::string binStr, int byteNum)
  {
    // out of bounds
    if(byteNum > (binStr.length() / 8))
    {
      std::cerr<<"::-> Error: invalid byte number\n";
      exit(1);
    }

    int byte=0, bit=-1;  // set the byte to zero

    for(int i=0; i<8; i++)
    {
      char toBeBit = binStr[8*(byteNum - 1) + i];
      if(isalpha(toBeBit))
      {
        std::cerr<<"\n::-> Error: The string must be composed of 0s and 1s.\n";
        exit(1);
      }
      // set the appropriate bit
      bit = toBeBit == '0' ? 0 : 1;
      byte = byte | (bit << (7-i));
    }

    return (uint)byte;
  }
}

#endif // _UTILS_