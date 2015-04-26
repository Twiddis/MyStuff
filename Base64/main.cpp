#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "encode.h"
#include "decode.h"

int main(int argc, char *argv[])
{
  int numOfLines;
  std::string argString;
  std::ifstream file;

  if ( argc != 3 )
  {
    std::cout << "Error: Invalid Arguments" << std::endl;
    std::cout << "Use switch -e for encoding" << std::endl;
    std::cout << "Use switch -d for decoding" << std::endl;
    return -1;
  }

  file.open(argv[1]);

  if ( !file.is_open() )
  {
    std::cout << "Error: File not opened" << std::endl;
    return -1;
  }

  numOfLines = 0;

  if ( *argv[2] == 'e' )
  {
    while ( getline(file, argString) )
    {
      std::cout << "Encoded Line " << numOfLines + 1 << ":" << std::endl;
      std::cout << encode(argString) << std::endl << std::endl;
      ++numOfLines;
    }

    std::cout << "Number of Lines Encoded: " << numOfLines << std::endl;
  }

  else if ( *argv[2] == 'd' )
  {
    while ( getline(file, argString) )
    {
      std::cout << "Decoded Line " << numOfLines + 1 << ":" << std::endl;
      std::cout << decode(argString) << std::endl << std::endl;
      ++numOfLines;
    }

    std::cout << "Number of Lines Decoded: " << numOfLines << std::endl;
  }
  else
  {
    std::cout << "Error: Invalid Arguments" << std::endl;
    std::cout << "Use switch -e for encoding" << std::endl;
    std::cout << "Use switch -d for decoding" << std::endl;
    return -1;
  }
  return 0;
}
