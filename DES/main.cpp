#include "DES.h"



int main()
{
	std::string input = "katthund";
	std::string key = "laksfisk";

	std::string hexInput = DES::plaintextToHexString(input);
	std::string hexKey = DES::plaintextToHexString(key);

	std::cout << "Input: \n\t" << hexInput << "\n";
	std::cout << "Key: \n\t" << hexKey << "\n";


	std::string cipherText = DES::encrypt(hexInput, hexKey);

	return 0;
}

