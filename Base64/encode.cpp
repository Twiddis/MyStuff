#include <string>
#include <vector>
#include <iostream>

#define BYTE 8
#define BLOCK 24
#define INDEXSIZE 6

#include "encode.h"

std::string encode(std::string argString)
{
  int i, j;
  std::vector<int> bigBitList;

  for ( i = 0; i < static_cast<int>(argString.size()); ++i )
  {
    int bitList[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int bits = 0;

    asciiToBinary(argString[i], bitList, &bits);

    for ( j = 0; j < 8; ++j )
      bigBitList.push_back(bitList[7 - j]);
  }
/*
  std::cout << "Bit List:" << std::endl;
  for ( i = 0; i < static_cast<int>(bigBitList.size()); ++i )
    std::cout << bigBitList[i];

  std::cout << std::endl;
*/
  return binaryToBase64(bigBitList);
}

void asciiToBinary(int character, int* bitList, int* bits)
{
  if ( character == 1 )
  {
    bitList[*bits] = 1;
    return;
  }
  else
  {
    int bit;

    if ( ( character % 2 ) == 0 )
    {
      bit = 0;
      character = character / 2;
      *bits += 1;
    }
    else
    {
      bit = 1;
      character = character / 2;
      *bits += 1;
    }

    asciiToBinary(character, bitList, bits);
    *bits -= 1;
    bitList[*bits] = bit;
  }
}

std::string binaryToBase64(std::vector<int> bigBitList)
{
  int i, j;
  std::string encodedString = "";
  std::vector<int> indexBitList;

  if ( bigBitList.size() % BLOCK == BYTE )
    for ( i = 0; i < BYTE * 2; ++i )
      bigBitList.push_back(0);

  else if ( bigBitList.size() % BLOCK == BYTE * 2)
    for ( i = 0; i < BYTE; ++ i )
      bigBitList.push_back(0);

/*
  std::cout << "Modified Bit List:" << std::endl;
  for ( i = 0; i < static_cast<int>(bigBitList.size()); ++i )
    std::cout << bigBitList[i];
*/

  for ( i = 0; i < static_cast<int>(bigBitList.size()) / INDEXSIZE; ++i )
  {
    for ( j = 0; j < INDEXSIZE ; ++j )
      indexBitList.push_back(bigBitList[(i) * INDEXSIZE + j]);
/*
    std::cout << "Broken Bits: " << std::endl;
    for ( j = 0; j < INDEXSIZE; ++j )
      std::cout << indexBitList[j];
    std::cout << std::endl;
  */

    encodedString += indexToChar(binaryToIndex(indexBitList));

    indexBitList.clear();
  }

  return encodedString;
}

int binaryToIndex(std::vector<int> indexBitList)
{
  int currentBit = 5, bitValue = 1, index = 0;

  while (currentBit >= 0)
  {
    index += indexBitList[currentBit] * bitValue;
    --currentBit;
    bitValue *= 2;
  }

  return index;
}

char indexToChar(int index)
{
  if ( index > 0 && index < 26 )
    return static_cast<char>(index + 65);
  else if ( index >= 26 && index < 52 )
    return static_cast<char>(index - 26 + 97);
  else if ( index >= 52 && index < 62)
    return static_cast<char>(index - 52 + 48);
  else if ( index == 62 )
    return '+';
  else if ( index == 63 )
    return '/';
  else if ( index == 0 )
    return '=';
  else
  {
    std::cout << "Error: Invalid Index: " << index << std::endl;
    return '%';
  }
}
