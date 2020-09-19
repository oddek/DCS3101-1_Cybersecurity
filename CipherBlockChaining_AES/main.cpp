#include "../AES/AES.h"

int BLOCKSIZE = 16;


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
		if(b1 < 0x10) stream << 0;
		stream << std::hex << (b1 ^ b2);
	}

	return stream.str();
}

std::string encryptCBC(std::string message, std::string key, std::string IV)
{
	std::string plaintext = plaintextToHexString(message);
	//std::cout << "Input as HEX:\n\t" << plaintext <<  "\nLength: \n\t" << plaintext.size() << "\n";
	addPadding(plaintext, BLOCKSIZE);
	std::cout << "Input after padding: \n\t" << plaintext <<  "\nLength: \n\t" << plaintext.size() << "\n";

	std::string ciphertext = "";
	std::string currentXOR = IV;
	for(int i = 0; i < plaintext.size(); i+=BLOCKSIZE)
	{
		std::string s = plaintext.substr(i, BLOCKSIZE);
		std::cout << "S before xor: \n\t" << s << "\n";

		s = hexStringXOR(s, currentXOR);
		std::cout << "S after xor: \n\t" << s << "\n";
		//std::string encrypted = AES::encrypt128BitMessage(s, key);
		//currentXOR = encrypted;
		//ciphertext += encrypted;

	}



	return ciphertext;
}


int main()
{

	std::string message = "Dette er en melding som burde bli sendtveldigfort";
	std::string key = 	"2b7e151628aed2a6abf7158809cf4f3c";
	std::string IV = 	"000102030405060708090a0b0c0d0e0f";
	std::string ciphertext = encryptCBC(message, key, IV);
	std::cout << "CipherText: \n\t" << ciphertext << "\n";

	/*bool test = true;

	if(test) 
	{
		AES::runTests();
		return 0;
	}

	std::string plaintext = 	"hundkattfisklaks";

	std::string key = 	"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	
	std::cout << "Plaintext:\n\t" << plaintext << "\n";
	std::cout << "Plaintext in hex: \n\t" << AES::plaintextToHexString(plaintext) << "\n";
	std::cout << "Key: \n\t" << key << "\n";

	std::string encrypted = AES::encrypt128BitMessage(AES::plaintextToHexString(plaintext), key);
	std::cout << "EncryptedMessage: \n\t" << encrypted << "\n";

	std::string decrypted = AES::decrypt128BitMessage(encrypted, key);
	std::cout << "DecryptedMessage: \n\t" << decrypted << "\n";

	std::string decPlain = AES::hexStringToPlaintext(decrypted);
	std::cout << "DecryptedPlainText: \n\t" << decPlain << "\n";

*/
	return 0;
}