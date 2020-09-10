#include <string>
#include <iostream>
#include <memory>
#include "Rotor.h"
#include "Enigma.h"




int main()
{
	
	//auto rotor1 = new Rotor(alphabets[0]);
	Enigma enigma;
	//Choose rotors 1-8 - Left to right;
	int rotors[3] = {1,2,3};
	//Set offset 1-26 - Left to right;
	int offset[3] = {1,1,1};
	int ringSetting[3] = {1,1,1};

	enigma.setRotors(rotors);
	enigma.setOffset(offset);
	enigma.setRingSetting(ringSetting);

	std::string input = "AAAAAA";
	std::cout << "Input: " << input << "\n";

	std::string encrypted = enigma.transform(input);
	std::cout << "Encrypted: " << encrypted << "\n";


	enigma.setOffset(offset);
	std::string decrypted = enigma.transform(encrypted);
	std::cout << "Decrypted: " << decrypted << "\n";
}