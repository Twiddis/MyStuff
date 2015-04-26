std::string encode(std::string argString);
void asciiToBinary(int character, int* bitList, int* bits);
std::string binaryToBase64(std::vector<int> bigBitList);
int binaryToIndex(std::vector<int> indexBitList);
char indexToChar(int index);
