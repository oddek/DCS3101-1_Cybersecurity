#include "AES.h"

int main()
{
	bool test = true;
	bool randomKey = false;

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

	return 0;
}

