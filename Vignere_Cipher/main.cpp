#include <iostream>
#include <string>
#include <algorithm>


int STARTASCIILOWER = 97;
int STOPASCIILOWER = 122;
int STARTASCIIUPPER = 65;
int STOPASCIIUPPER = 90;

/*
As the %-operator does not behave like modulo on negative numbers, this function is necessary
*/
int modulo(int a, int b)
{
	return (a % b + b) % b;
}

char shiftChar(char c,  char shiftBy, bool backward = false)
{	
	/*
	Checking if the characters upper or lower case, and chooses the asciiboundaries of the respective set.
	*/
	int startAscii = (c >= STARTASCIILOWER) ? STARTASCIILOWER : STARTASCIIUPPER;
	int stopAscii = (c >= STARTASCIILOWER) ? STOPASCIILOWER : STOPASCIIUPPER;

	/*
	Move the character downto the 0-25 range, performing the shift, and moving it back up the correct asciirange. 
	*/
	char output = c - startAscii;
	if(backward)
	{
		output = modulo((output - (shiftBy - STARTASCIILOWER)), (stopAscii - startAscii + 1)) + startAscii;
	}
	else
	{
		output = modulo((output + (shiftBy - STARTASCIILOWER)), (stopAscii - startAscii + 1)) + startAscii;
	}
	return output;
}

std::string encrypt(std::string plainText, std::string key)
{
	int keyIndex = 0;
	std::string cipherText;
	for(int i = 0; i < plainText.size(); i++)
	{
		/*
		Dont encrypt spaces, commas and periods.
		*/
		if(plainText[i] == ' ' || plainText[i] == '.' || plainText[i] == ',')
		{
			cipherText += plainText[i];
			continue;
		}
		cipherText += (shiftChar(plainText[i], key.at(keyIndex)));
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
		/*
		Dont decrypt spaces, commas and periods.
		*/
		if(cipherText[i] == ' ' || cipherText[i] == '.' || cipherText[i] == ',')
		{
			plainText += cipherText[i];
			continue;
		}

		plainText += (shiftChar(cipherText[i], key.at(keyIndex), true));
		keyIndex = (keyIndex + 1) % key.size();
	}
	return plainText;
}


int main(int argc, char* argv[]) 
{
	/*
	Mostly commandline argument handling
	*/
	if(argc < 4)
	{
		std::cout << "Wrong number of arguments passed\n";
		std::cout << "Arguments: \n\t./Vignere cipher -e/d <string> <key> <optionalSecondKey>\n";
		return -1;
	}

	std::string input = argv[2];
	std::string key = argv[3];
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);
	std::string key2 = "";
	if(argc > 4)
	{	
		key2 = argv[4];
		std::transform(key2.begin(), key2.end(), key2.begin(), ::tolower);
	}
	std::string output;

	if(std::string(argv[1]) == "-e")
	{
		output = encrypt(input, key);

		if(key2.compare("") != 0)
		{
			output = encrypt(output, key2); 
		}
	}
	else if(std::string(argv[1]) == "-d")
	{
		output = decrypt(input, key);

		if(key2.compare("") != 0)
		{
			output = decrypt(output, key2);
		}
	}
	else
	{
		std::cout << "Error, expected arguments:\n\t/Vignere cipher -e/d <string> <key> <optionalSecondKey>\n";

		return -1;
	}
	std::cout << "\nInput:\t\t" << input << "\n";
	std::cout << "Key:\t\t" << key << "\n";
	if(key2.compare("") != 0) std::cout << "Key2:\t\t" << key2 << "\n";
	std::cout << "Output:\t\t" << output << "\n"; 
	return 0;
}