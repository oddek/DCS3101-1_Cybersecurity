#include "../AES/AES.h"

int BLOCKSIZE = 16*2;


void addPadding(std::string& s, int blockSize)
{
	std::stringstream stream;

	stream << std::hex << 0x01;
	for(int i = 0; i < blockSize - ((s.size() + 1) % blockSize); i++)
	{
		stream << std::hex << 0x00;
	}

	s += stream.str();
}

void removePadding(std::string& s)
{
	auto it = s.end() - 1;
	while(*it == '0')
	{
		it = s.erase(it);
		it--;
	}
	s.erase(it);

}
std::string plaintextToHexString(std::string plaintext)
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

std::string hexStringXOR(const std::string& a, const std::string& b)
{
	std::stringstream stream;

	for(int i = 0; i < a.size(); i+=2)
	{
		unsigned long b1 = stoi(a.substr(i, 2), 0, 16);
		unsigned long b2 = stoi(b.substr(i, 2), 0, 16);
		b1 ^= b2;
		if(b1 < 16) stream << 0;
		stream << std::hex << (b1);
	}

	return stream.str();
}

std::string hexStringToPlaintext(std::string s)
{
	std::string plain = "";
	for(int i = 0; i < s.size(); i+=2)
	{
		char temp = stoul(s.substr(i, 2), 0, 16);
		plain += temp;
	}
	return plain;
}


std::string encryptCBC(std::string plaintext, std::string key, std::string IV)
{
	
	addPadding(plaintext, BLOCKSIZE);

	std::string ciphertext = "";
	std::string currentXOR = IV;
	for(int i = 0; i < plaintext.size(); i+=BLOCKSIZE)
	{
		std::string s = plaintext.substr(i, BLOCKSIZE);
		s = hexStringXOR(s, currentXOR);

		std::string encrypted = AES::encrypt128BitMessage(s, key);
		currentXOR = encrypted;
		ciphertext += encrypted;

	}
	return ciphertext;
}

std::string decryptCBC(std::string ciphertext, std::string key, std::string IV)
{
	std::string plaintext = "";

	std::string currentXOR = IV;

	for(int i = 0; i < ciphertext.size(); i+=BLOCKSIZE)
	{
		std::string s = ciphertext.substr(i, BLOCKSIZE);
		std::string decrypted = AES::decrypt128BitMessage(s, key);
		decrypted = hexStringXOR(decrypted, currentXOR);
		currentXOR = s;
		plaintext += decrypted;

	}
	removePadding(plaintext);

	return plaintext;
}
//From: https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf
//PAGE 27
void runTest()
{
	std::string IV = 	"000102030405060708090a0b0c0d0e0f";
	std::string key = 	"2b7e151628aed2a6abf7158809cf4f3c";
	std::string plain = "6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411e5fbc1191a0a52eff69f2445df4f9b17ad2b417be66c3710";
	std::string ciphertext = "7649abac8119b246cee98e9b12e9197d5086cb9b507219ee95db113a917678b273bed6b8e3c1743b7116e69e222295163ff1caa1681fac09120eca307586e1a7";

	std::string encrypted = encryptCBC(plain, key, IV);

	std::cout << "Running test:\n";

	std::cout << "Test 1: \n";
	std::cout << "\tEncryption: ";

	if(encrypted.compare(0, ciphertext.size(), ciphertext) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}

	std::string decrypted = decryptCBC(encrypted, key, IV);

	std::cout << "\tDecryption: ";

	if(decrypted.compare(0, plain.size(), plain) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}

}


int main()
{
	bool test = true;
	if(test)
	{
		runTest();
		return 0;
	}

	std::string message = "Dette er en melding som burde bli sendtveldigfort";
	std::string IV = 	"000102030405060708090a0b0c0d0e0f";
	std::string key = 	"2b7e151628aed2a6abf7158809cf4f3c";
	std::string ciphertext = encryptCBC(plaintextToHexString(message), key, IV);
	std::cout << "CipherText: \n\t" << ciphertext << "\n";


	std::string decrypted = decryptCBC(ciphertext, key, IV);
	std::cout << "Decrypted: \n\t" << decrypted << "\n";
	std::cout << "Decrypted: \n\t" << hexStringToPlaintext(decrypted) << "\n";
	
	return 0;
}

