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
    if((uint)byteNum > (binStr.length() / 8))
    {
      std::cerr<<"::-> Error: invalid byte number\n";
      exit(1);
    }

    int byte=0, bit=-1;  // set the byte to zero

    for(int i=0; i<8; i++)
    {
      char toBeBit = binStr[8*(byteNum - 1) + i];
      if(toBeBit != '0' && toBeBit != '1')
      {
        std::cerr<<"::-> Error: The string must be composed of 0s and 1s with no spaces.\n";
        exit(1);
      }
      // set the appropriate bit
      bit = toBeBit == '0' ? 0 : 1;
      byte = byte | (bit << (7-i));
    }

    return (uint)byte;
  }
  // convert the bin string to readable string
  std::string binStrToReadable(std::string binStr, uint byteNum)
  {
    // alloc the readStr
    char *readStr = new char[byteNum+1];
    std::string finalStr;

    for(uint i=0; i<byteNum; i++)
    {
      // get byte and set it
      readStr[i] = byteFromBinStr(binStr, i+1);
    }
    // avoid junk
    readStr[byteNum] = '\0';
    finalStr = std::string(readStr);
    // free the readStr
    delete[] readStr;
    return finalStr;
  }
  // get the next bit from the bin str
  int getNextBitFrom(std::string binStr, uint __cov_len)
  {
    if(__cov_len > (uint)binStr.length() - 1)
    {
      // reset cov_len and return -1
      __cov_len = 0;
      return -1;
    }
    char toBeBit = binStr[__cov_len];
    if(toBeBit != '0' && toBeBit != '1')
    {
      std::cerr<<"::-> Error: The string must be composed of 0s and 1s.\n";
      exit(1);
    }
    // got the bit
    int bit = toBeBit == '0' ? 0 : 1;
    return bit;
  }
}

#endif // _UTILS_