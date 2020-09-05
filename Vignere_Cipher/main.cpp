
#include <iostream>
#include <string>

int STARTASCII = 97;//32;
int STOPASCII = 122;//126;

char shiftCharForward( char c,  char shiftBy)
{	
	char output = c - STARTASCII;
	output = (output + (shiftBy - STARTASCII)) % (STOPASCII - STARTASCII + 1);
	return output + STARTASCII;
}

int negMod(int a, int b)
{
	return (a % b + b) % b;
}

char shiftCharBackward( char c,  char shiftBy)
{	
	char output = c - STARTASCII;
	output = negMod((output - (shiftBy - STARTASCII)), (STOPASCII - STARTASCII + 1));
	return output + STARTASCII;
}

std::string encrypt(std::string plainText, std::string key)
{
	int keyIndex = 0;
	std::string cipherText;
	for(int i = 0; i < plainText.size(); i++)
	{
		cipherText += (shiftCharForward(plainText[i], key.at(keyIndex)));
		keyIndex = (keyIndex + 1) % key.size();
	}
	return cipherText;
}

std::string decrypt(std::string cipherText, std::string key)
{
	int keyIndex = 0;
	std::string plainText;
	for(int i = 0; i < cipherText.size(); i++)
	{
		plainText += (shiftCharBackward(cipherText[i], key.at(keyIndex)));
		keyIndex = (keyIndex + 1) % key.size();
	}
	return plainText;
}


int main(int argc, char* argv[]) 
{
	if(argc != 4)
	{
		std::cout << "Wrong number of arguments passed";
		return -1;
	}

	std::string input = argv[2];
	std::string key = argv[3];
	std::string output;
	std::string inverse;
	if(std::string(argv[1]) == "-e")
	{
		output = encrypt(input, key);
		inverse = decrypt(output, key);
	}
	else if(std::string(argv[1]) == "-d")
	{
		output = decrypt(input, key);
		inverse = encrypt(output, key);
	}
	else
	{
		std::cout << "Wrong input code, must be -e or -d";
		return -1;
	}
	std::cout << "Input:   " << input << "\n";
	std::cout << "Key:     " << key << "\n";
	std::cout << "Output:  " << output << "\n"; 
	std::cout << "Inverse: " << inverse << "\n"; 
	return 0;
}