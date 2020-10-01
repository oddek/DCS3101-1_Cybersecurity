#include "DES.h"

std::string DES::plaintextToHexString(std::string plaintext)
{
	std::stringstream stream;
	for(auto ch : plaintext)
	{
		unsigned long num = ch;
		if(num < 16) stream << 0;
		stream << std::hex << num;
	}
	std::string res(stream.str());
	return res;
}

std::string DES::hexStringToPlaintext(std::string s)
{
	std::string plain = "";
	for(int i = 0; i < s.size(); i+=2)
	{
		char temp = stoul(s.substr(i, 2), 0, 16);
		plain += temp;
	}
	return plain;
}

std::string DES::encrypt(std::string plainText, std::string key)
{
	auto allKeys = generateSubKeys(key);
	std::string cipherText = "";




	return cipherText;


}

std::string DES::generateSubKeys(std::string key)
{
	
	return "";
}